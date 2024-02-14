#include "MQTTservice.h"

/**
 * @brief MQTTpublisher class.
 * Publish messages to an MQTT broker.
 * @implements MQTTservice
 * @extends MQTTservice
 */
class MQTTpublisher : public MQTTservice
{
public:

    /**
     * @brief Construct a new MQTTpublisher object.
     * @param server The MQTT broker server.
     * @param client_id The MQTT client ID.
     * @param topic The MQTT topic.
     */
    MQTTpublisher(const char *server, const char *client_id, const char *topic)
        : MQTTservice(server, client_id, topic) {}

    /**
     * @brief Construct a new MQTTpublisher object.
     * @param server The MQTT broker server.
     * @param client_id The MQTT client ID.
     */
    MQTTpublisher(const char *server, const char *client_id)
        : MQTTservice(server, client_id) {}

    /**
     * @brief Publish a message to a topic (a \ref PubSubClient::publish wrapper).
     * @param topic The topic to publish to.
     * @param payload The payload to publish.
     */
    void publish(const char *topic, const char *payload);

    /**
     * @brief Publish a message to the default topic (a \ref PubSubClient::publish wrapper).
     * @param payload The payload to publish.
     */
    void publish(const char *payload);
    
    /**
     * @brief Publish a JSON message to a topic.
     * @param topic The topic to publish to.
     * @param JSONfield The field of the JSON message.
     * @param JSONvalue The value of the JSON message.
     */
    void publishJSON(const char *topic, const char *JSONfield, const char *JSONvalue);
};