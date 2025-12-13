#include <WiFiHelper.h>
#include <MqttHelper.h>

const char* ssid = "***REMOVED***";
const char* password = "***REMOVED***";

WifiHelper wifi(ssid, password);
MqttHelper mqtt("192.168.178.128", 1883, "smarthome", "***REMOVED***");

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