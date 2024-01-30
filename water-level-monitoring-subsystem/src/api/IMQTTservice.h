// IMQTTservice.h
#ifndef IMQTT_SERVICE_H
#define IMQTT_SERVICE_H
class IMQTTservice
{
public:
    virtual ~IMQTTservice() = default;
    virtual void setMqttServer(char *mqtt_server) = 0;
    virtual void setTopic(char *topic) = 0;
    virtual void setMessage(char *message) = 0;
    virtual void reconnect() = 0;
    virtual char *getMqttServer() = 0;
    virtual char *getTopic() = 0;
    virtual char *getMessage() = 0;

protected:
    char *mqtt_server;
    char *topic;
    char *message;
};
#endif // IMQTT_SERVICE_H