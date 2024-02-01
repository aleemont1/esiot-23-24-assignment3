#include <ArduinoJson.h>
#include "../api/MQTTsubscriber.h"
#include "../env/config.h"

void MQTTsubscriber::subscribeJSON(const char *topic)
{
    this->mqttClient.subscribe(topic);
    this->mqttClient.setCallback([this](char *topic, byte *payload, unsigned int length)
                                 { this->callbackJSON(topic, payload, length); });
}

void MQTTsubscriber::callbackJSON(char *topic, byte *payload, unsigned int length)
{
    /*
        Serial.print("Message arrived [");
        Serial.print(topic);
        Serial.print("] ");
        for (int i = 0; i < length; i++)
        {
            Serial.print((char)payload[i]);
        }
        Serial.println();
    */
    // Deserialize JSON payload
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload, length);

    // Check for deserialization error
    if (error.code() != DeserializationError::Ok)
    {
        Serial.print("Deserialization error: ");
        Serial.println(error.c_str());
        this->callback(topic, payload, length);
        return;
    }

    // Get the "FREQ" field's value
    int freq = doc["FREQ"];
    if (freq != 0)
    {
        this->setSavedPayload(freq);
        // Serial.println("NEW payload: " + String((int)this->getSavedPayloadInt()));
    }
}

void MQTTsubscriber::subscribe(const char *topic)
{
    this->mqttClient.subscribe(topic);
    this->mqttClient.setCallback([this](char *topic, byte *payload, unsigned int length)
                                 { this->callback(topic, payload, length); });
}

void MQTTsubscriber::callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    this->setSavedPayload(payload);
}

void MQTTsubscriber::setSavedPayload(byte *payload)
{
    this->saved_payload = payload;
}

byte *MQTTsubscriber::getSavedPayload()
{
    return this->saved_payload;
}

void MQTTsubscriber::setSavedPayload(int payload)
{
    this->saved_payload_int = payload;
}

int MQTTsubscriber::getSavedPayloadInt()
{
    return this->saved_payload_int;
}