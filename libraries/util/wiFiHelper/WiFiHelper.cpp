#include "WiFiHelper.h"

WiFiHelper::WiFiHelper(const char* ssid, const char* password) {
    this->ssid = ssid;
    this->password = password;
}

void WiFiHelper::begin() {
    Serial.begin(9600);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("Status: ");
        Serial.println(WiFi.status());
        Serial.println("Connecting to WLAN...");
    }

    Serial.println("Connected to WLAN");
}

void WiFiHelper::reconnect() {
    if (WiFi.status() == WL_CONNECTED) return;

    Serial.println("WLAN lost. Attempting to reconnect...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Reconnecting...");
    }

    Serial.println("Reconnected to WLAN");
}

bool WiFiHelper::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}