#include "../api/MQTTsubscriber.h"

void MQTTsubscriber::subscribe(const char* topic) {
        this->mqttClient.subscribe(topic);
        this->mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
            this->callback(topic, payload, length);
        });
    }

void MQTTsubscriber::callback(char* topic, byte* payload, unsigned int length) {
        Serial.print("Message arrived [");
        Serial.print(topic);
        Serial.print("] ");
        for (int i = 0; i < length; i++) {
            Serial.print((char)payload[i]);
        }
        Serial.println();
}