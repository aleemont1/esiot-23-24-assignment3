#include "../api/MQTTpublisher.h"
#include <arduinoJS

void MQTTpublisher::publish(const char* topic, const char* payload) {
        this->mqttClient.publish(topic, payload);
    }

void MQTTpublisher::publish(const char* payload) {
        this->mqttClient.publish(this->mqtt_topic, payload);
    }