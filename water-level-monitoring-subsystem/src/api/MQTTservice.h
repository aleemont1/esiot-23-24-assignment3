#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <PubSubClient.h>
#include <WiFiClient.h>
/**
 * @brief MQTTservice class.
 * Basic MQTT service.
*/
class MQTTservice
{
protected:
    const char *mqtt_server;
    const char *mqtt_client_id;
    const char *mqtt_topic;

    WiFiClient espClient;
    PubSubClient mqttClient;

public:

    /**
     * @brief Construct a new MQTTservice object.
     * @param server The MQTT broker server.
     * @param client_id The MQTT client ID.
     * @param topic The MQTT topic.
    */
    MQTTservice(const char *server, const char *client_id, const char *topic)
        : mqtt_server(server), mqtt_client_id(client_id), mqtt_topic(topic), mqttClient(espClient) {}
    
    /**
     * @brief Construct a new MQTTservice object.
     * @param server The MQTT broker server.
     * @param client_id The MQTT client ID.
    */
    MQTTservice(const char *server, const char *client_id)
        : mqtt_server(server), mqtt_client_id(client_id), mqttClient(espClient) {}
    
    /**
     * @brief Connect to MQTT broker.
     */
    void connect();
    
    /**
     * @brief Loop function (a \ref PubSubClient::loop wrapper).
     */
    void loop();

    /**
     * @brief Check if the client is connected to the MQTT broker (a \ref PubSubClient::connected wrapper).
     * @return true if connected, false otherwise.
    */
    bool connected();
};

#endif // MQTT_SERVICE_H