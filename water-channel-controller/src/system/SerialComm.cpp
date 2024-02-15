#include "SerialComm.h"

void SerialComm::serialCommunication()
{
    String receivedContent;
    String valveValue;
    if (Serial.available())
    {
        receivedContent = Serial.readStringUntil('\n');
        JsonDocument doc;
        deserializeJson(doc, receivedContent);
        String status = doc["status"];

        if (status == "ALARM_TOO_LOW")
        {
            Serial.println("{\"status\": \"ALARM_TOO_LOW\",\"valveValue\": 0}");
        }
        else if (status == "NORMAL")
        {
            Serial.println("{\"status\":\"NORMAL\",\"valveValue\": 25}");
        }
        else if (status == "PRE_ALARM_TOO_HIGH")
        {
            Serial.println("{\"status\":\"PRE_ALARM_TOO_HIGH\",\"valveValue\": 40}");
        }
        else if (status == "ALARM_TOO_HIGH")
        {
            Serial.println("{\"status\":\"ALARM_TOO_HIGH\",\"valveValue\": 50}");
        }
        else if (status == "ALARM_TOO_HIGH_CRITIC")
        {
            Serial.println("{\"status\":\"ALARM_TOO_HIGH_CRITIC\",\"valveValue\": 100}");
        }
        else
        {
            valveValue = "unknown state";
        }
    }
}