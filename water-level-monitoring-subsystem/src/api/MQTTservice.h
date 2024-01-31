#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <PubSubClient.h>
#include <WiFiClient.h>

class MQTTservice
{
protected:
    const char *mqtt_server;
    const char *mqtt_client_id;
    const char *mqtt_topic;

    WiFiClient espClient;
    PubSubClient mqttClient;

public:
    MQTTservice(const char *server, const char *client_id, const char *topic)
        : mqtt_server(server), mqtt_client_id(client_id), mqtt_topic(topic), mqttClient(espClient) {}

    void connect();

    void loop();
};

#endif // MQTT_SERVICE_H