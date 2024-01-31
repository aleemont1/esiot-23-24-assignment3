#include "MQTTservice.h"

class MQTTsubscriber : public MQTTservice {
public:
    MQTTsubscriber(const char* server, const char* client_id)
        : MQTTservice(server, client_id) {}

    void subscribe(const char* topic);
    void callback(char* topic, byte* payload, unsigned int length);
};