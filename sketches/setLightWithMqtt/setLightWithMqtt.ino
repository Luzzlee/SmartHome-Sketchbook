#include <WiFiHelper.h>
#include <MqttHelper.h>
#include "arduino_secrets.h"

// Output pin driving the light. Adjust to match your wiring.
const int LIGHT_PIN = 2;

// Command topic this device listens on for on/off commands from the backend,
// matching the schema smarthome/light/<name>/<id> used by DevicesService.SwitchLight.
// The backend lowercases the device name (but not the id) when building this topic,
// so the name portion is lowercased here too to match regardless of how DEVICE_NAME
// is capitalized in arduino_secrets.h.
const String commandTopic = String("smarthome/light/") + String(DEVICE_NAME).toLowerCase() + "/" + DEVICE_ID;

WiFiHelper wifi(WIFI_SSID, WIFI_PASSWORD);
MqttHelper mqtt("192.168.178.128", 1883, MQTT_USERNAME, MQTT_PASSWORD, commandTopic.c_str());

void onMqttMessage(String topic, String payload) {
  if (payload == "ON") {
    digitalWrite(LIGHT_PIN, HIGH);
    Serial.println("Light switched ON");
  } else if (payload == "OFF") {
    digitalWrite(LIGHT_PIN, LOW);
    Serial.println("Light switched OFF");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT_PIN, OUTPUT);
  wifi.begin();
  mqtt.setCallback(onMqttMessage);
  mqtt.begin();
}

void loop() {
  wifi.reconnect();
  mqtt.reconnect();
  mqtt.loop();
}
