#include "MQTTservice.h"

class MQTTsubscriber : public MQTTservice {
public:
    MQTTsubscriber(const char* server, const char* client_id)
        : MQTTservice(server, client_id) {}

    void subscribe(const char* topic);
    void callback(char* topic, byte* payload, unsigned int length);
    void subscribeJSON(const char *topic);
    void callbackJSON(char *topic, byte *payload, unsigned int length);
    void setSavedPayload(byte *payload);
    byte *getSavedPayload();
    void setSavedPayload(int payload);
    int getSavedPayloadInt();
private:
    byte *saved_payload;
    int saved_payload_int;
};