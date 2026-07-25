#include <WiFiNINA.h>
#include <PubSubClient.h>

#include "WiFiConnection.ino"
#include "arduino_secrets.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* mqtt_server = "192.168.178.128";
const int mqtt_port = 1883;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(WiFi.status());
    Serial.println("Connecting to WLAN...");
  }
  Serial.println("Connected to WLAN");

  client.setServer(mqtt_server, mqtt_port);
  while(!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    if (client.connect("ArduinoClient", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("Conntected to MQTT Broker");
    } else {
      Serial.print("Error, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
  
  client.publish("smarthome/light/arduino1/20250909-001", "Arduino is online");
}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WLAN lost. Attempting to reconnect...");
  }
  while(!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    if (client.connect("ArduinoClient", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("Conntected to MQTT Broker");
      client.publish("smarthome/light/arduino1/20250909-001", "Arduino is online");
    } else {
      Serial.print("Error, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.loop();
}