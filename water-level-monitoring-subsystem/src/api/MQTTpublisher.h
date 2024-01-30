// MQTTpublisher.h
#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#include "MQTTservice.h"

class MQTTpublisher : public MQTTservice
{
public:
    MQTTpublisher() : MQTTservice() {};
    MQTTpublisher(char *mqtt_server, char *topic) : MQTTservice(mqtt_server, topic) {};
    MQTTpublisher(char *mqtt_server) : MQTTservice(mqtt_server) {};
    ~MQTTpublisher() = default;
    void publish();
};

#endif // MQTT_PUBLISHER_H