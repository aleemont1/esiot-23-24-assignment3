#include "MQTTservice.h"

class MQTTsubscriber : public MQTTservice
{
public:

    /**
     * @brief Construct a new MQTTsubscriber object.
     * @param server The MQTT broker server.
     * @param client_id The MQTT client ID.
     */
    MQTTsubscriber(const char *server, const char *client_id)
        : MQTTservice(server, client_id) {}

    /**
     * @brief Subscribe to a topic.
     * @param topic The topic to subscribe to.
     */
    void subscribe(const char *topic);

    /**
     * @brief Callback function for MQTT messages (see \ref PubSubClient::callback).
     * @param topic The topic of the message.
     * @param payload The payload of the message.
     * @param length The length of the payload.
     */
    void callback(char *topic, byte *payload, unsigned int length);
    
    /**
     * @brief Subscribe to a topic and parse the payload as JSON (a \ref PubSubClient::subscribe wrapper).
     * @param topic The topic to subscribe to.
     */
    void subscribeJSON(const char *topic);
    
    /**
     * @brief Callback function for MQTT messages (see \ref PubSubClient::callback).
     * @param topic The topic of the message.
     * @param payload The payload of the message.
     * @param length The length of the payload.
     */
    void callbackJSON(char *topic, byte *payload, unsigned int length);
    
    /**
     * @brief Set the local payload.
     * @param payload The payload to save.
     */
    void setSavedPayload(byte *payload);
    
    /**
     * @brief Get the local payload.
     * @return byte* : The local payload.
     */
    byte *getSavedPayload();
    
    /**
     * @brief Set the local int payload.
     * @param payload The payload to save.
     */
    void setSavedPayload(int payload);
    
    /**
     * @brief Get the local int payload.
     * @return int : The local int payload.
     */
    int getSavedPayloadInt();

private:
    byte *saved_payload;
    int saved_payload_int;
};