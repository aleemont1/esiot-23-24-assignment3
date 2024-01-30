// MQTTservice.h
#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include "IMQTTservice.h"

class MQTTservice : public IMQTTservice
{
public:
    MQTTservice();
    MQTTservice(char *mqtt_server, char *topic);
    MQTTservice(char *mqtt_server);
    void setMqttServer(char *mqtt_server) override;
    void setTopic(char *topic) override;
    void setMessage(char *message) override;
    void reconnect() override;
    char *getMqttServer() override;
    char *getTopic() override;
    char *getMessage() override;
};

#endif // MQTT_SERVICE_H