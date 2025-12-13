#ifndef WIFIHELPER_H
#define WIFIHELPER_H

#include <Arduino.h>
#include <WiFiNINA.h>

class WiFiHelper {
    private:
        const char* ssid;
        const char* password;

    public:
        WiFiHelper(const char* ssid, const char* password);

        void begin();
        void reconnect();
        bool isConnected();
};

#endif