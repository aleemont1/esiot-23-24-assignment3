#include "../api/MQTTservice.h"
#include "../env/constants.h"

MQTTservice::MQTTservice()
{
    this->setMqttServer(default_mqtt_server);
}

MQTTservice::MQTTservice(char *mqtt_server, char *topic)
{
    this->setMqttServer(mqtt_server);
    this->setTopic(topic);
}

MQTTservice::MQTTservice(char *mqtt_server)
{
    this->setMqttServer(mqtt_server);
}

void MQTTservice::setMqttServer(char *mqtt_server)
{
    this->mqtt_server = mqtt_server;
}

void MQTTservice::setTopic(char *topic)
{
    this->topic = topic;
}

void MQTTservice::setMessage(char *message)
{
    this->message = message;
}

char *MQTTservice::getMqttServer()
{
    return this->mqtt_server;
}

char *MQTTservice::getTopic()
{
    return this->topic;
}

char *MQTTservice::getMessage()
{
    return this->message;
}
