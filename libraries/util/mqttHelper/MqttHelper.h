#ifndef MQTTHELPER_H
#define MQTTHELPER_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

typedef void (*MessageCallback)(String topic, String payload);

class MqttHelper {
  private:
    const char* server;
    int port;
    const char* user;
    const char* password;
    const char* commandTopic;

    WiFiClient wifiClient;
    PubSubClient client;

    static MessageCallback callback;

    static void OnMqttReceived(char *topic, byte *payload, unsigned int length);
  public:
    MqttHelper(const char* mqttServer, int mqttPort, const char* mqttUser, const char* mqttPassword, const char* deviceCommandTopic);

    void begin();
    void reconnect();
    void loop();
    void publish(const char* topic, const char* payload);
    void subscribe(const char* topic);

    void setCallback(MessageCallback cb);
};

#endif
