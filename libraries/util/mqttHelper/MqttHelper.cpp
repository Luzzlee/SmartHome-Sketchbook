#include "MqttHelper.h"

MessageCallback MqttHelper::callback = nullptr;

MqttHelper::MqttHelper(const char* mqttServer, int mqttPort, const char* mqttUser, const char* mqttPassword)
  : server(mqttServer), port(mqttPort), user(mqttUser), password(mqttPassword), client(wifiClient) {
}

void MqttHelper::begin() {
  Serial.begin(9600);

  client.setServer(server, port);
  client.setCallback(OnMqttReceived);
  reconnect();
}

void MqttHelper::reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    if (client.connect("ArduinoClient", user, password)) {
      Serial.println("Connected to MQTT Broker");
      publish("smarthome/light/arduino1/init", "Arduino is online");
    } else {
      Serial.print("Error, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void MqttHelper::loop() {
  client.loop();
}

void MqttHelper::publish(const char* topic, const char* payload) {
  client.publish(topic, payload);
}

void MqttHelper::setCallback(MessageCallback cb) {
  callback = cb;
}

void OnMqttReceived(char *topic, byte *payload, unsigned int length) {
  String content = "";
	for (size_t i = 0; i < length; i++) { 
    content.concat((char)payload[i]);
  }
  
  Serial.print("Received on: ");
  Serial.println(topic);
  Serial.print("Data: ");
  Serial.println(content);

  if (callback) {
    callback(String(topic), content);
  }
}