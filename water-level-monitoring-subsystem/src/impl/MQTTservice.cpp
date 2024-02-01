#include "../api/MQTTservice.h"

void MQTTservice::connect()
{
    // Connect to MQTT broker
    mqttClient.setServer(mqtt_server, 1883);
    while (!mqttClient.connected())
    {
        Serial.println("Connecting to MQTT broker...");
        if (mqttClient.connect(mqtt_client_id))
        {
            Serial.println("Connected to MQTT broker");
        }
        else
        {
            Serial.print("Failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" Retrying in 5 seconds");
            delay(5000);
        }
    }
}

void MQTTservice::loop()
{
    mqttClient.loop();
}

bool MQTTservice::connected()
{
    return mqttClient.connected();
}