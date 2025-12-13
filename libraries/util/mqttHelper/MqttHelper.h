#ifndef MQTTHELPER_H
#define MQTTHELPER_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

class MqttHelper {
  private:
    const char* server;
    int port;
    const char* user;
    const char* password;

    WiFiClient wifiClient;
    PubSubClient client;

    static MessageCallback callback;

    static void OnMqttReceived(char *topic, byte *payload, unsigned int length);
  public:
    MqttHelper(const char* mqttServer, int mqttPort, const char* mqttUser, const char* mqttPassword);

    void begin();
    void reconnect();
    void loop();
    void publish(const char* topic, const char* payload);

    void setCallback(MessageCallback cb);
};

#endif