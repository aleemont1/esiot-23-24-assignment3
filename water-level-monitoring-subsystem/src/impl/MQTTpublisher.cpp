#include "../api/MQTTpublisher.h"
#include <ArduinoJson.h>

void MQTTpublisher::publish(const char* topic, const char* payload) {
        this->mqttClient.publish(topic, payload);
    }

void MQTTpublisher::publish(const char* payload) {
        this->mqttClient.publish(this->mqtt_topic, payload);
    }

void MQTTpublisher::publishJSON(const char *topic, const char *JSONfield, const char *JSONvalue) {
        JsonDocument doc;
        doc[JSONfield] = JSONvalue;
        char buffer[200];
        serializeJson(doc, buffer);
        this->mqttClient.publish(topic, buffer);
    }