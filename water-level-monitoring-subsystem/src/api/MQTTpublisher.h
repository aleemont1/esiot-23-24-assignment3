#include "MQTTservice.h"

class MQTTpublisher : public MQTTservice {
public:
    MQTTpublisher(const char* server, const char* client_id, const char* topic)
        : MQTTservice(server, client_id, topic) {}
     MQTTpublisher(const char* server, const char* client_id)
        : MQTTservice(server, client_id) {}

    void publish(const char* topic, const char* payload);
    void publish(const char* payload);
    void publishJSON(const char *topic, const char *JSONfield, const char *JSONvalue);
};