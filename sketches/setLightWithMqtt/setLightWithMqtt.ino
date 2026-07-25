#include <WiFiHelper.h>
#include <MqttHelper.h>
#include "arduino_secrets.h"

WiFiHelper wifi(WIFI_SSID, WIFI_PASSWORD);
MqttHelper mqtt("192.168.178.128", 1883, MQTT_USERNAME, MQTT_PASSWORD);

void setup() {
  Serial.begin(9600);
  wifi.begin();
  mqtt.begin();
}

void loop() {
  wifi.reconnect();
  mqtt.reconnect();
  mqtt.loop();
}