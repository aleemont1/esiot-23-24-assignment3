// MQTTsubscriber.h
#ifndef MQTT_SUBSCRIBER_H
#define MQTT_SUBSCRIBER_H

#include "MQTTservice.h"

class MQTTsubscriber : public MQTTservice
{
public:
    MQTTsubscriber() : MQTTservice(){};
    MQTTsubscriber(char *mqtt_server, char *topic) : MQTTservice(mqtt_server, topic){};
    MQTTsubscriber(char *mqtt_server) : MQTTservice(mqtt_server){};
    ~MQTTsubscriber() = default;

    void subscribe();
};

#endif // MQTT_SUBSCRIBER_H