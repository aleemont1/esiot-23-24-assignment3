#include "SerialComm.h"

String SerialComm::createResponse(String status)
{
    if (status == "ALARM_TOO_LOW")
    {
        return "{\"status\": \"ALARM_TOO_LOW\",\"valveValue\": 0}";
    }
    else if (status == "NORMAL")
    {
        return "{\"status\":\"NORMAL\",\"valveValue\": 25}";
    }
    else if (status == "PRE_ALARM_TOO_HIGH")
    {
        return "{\"status\":\"PRE_ALARM_TOO_HIGH\",\"valveValue\": 40}";
    }
    else if (status == "ALARM_TOO_HIGH")
    {
        return "{\"status\":\"ALARM_TOO_HIGH\",\"valveValue\": 50}";
    }
    else if (status == "ALARM_TOO_HIGH_CRITIC")
    {
        return "{\"status\":\"ALARM_TOO_HIGH_CRITIC\",\"valveValue\": 100}";
    }
    else
    {
        return "unknown state";
    }
}

void SerialComm::serialCommunication()
{
    String receivedContent;
    if (Serial.available())
    {
        receivedContent = Serial.readStringUntil('\n');
        JsonDocument doc;
        deserializeJson(doc, receivedContent);
        String status = doc["status"];
        String response = createResponse(status);
        Serial.println(response);
    }
}