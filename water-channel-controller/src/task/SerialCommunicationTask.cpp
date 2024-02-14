#include "task/SerialCommunicationTask.h"
#include "system/Logger.h"
#define DEBUG

SerialCommunicationTask::SerialCommunicationTask(int period, JsonProcessor jsonProcessor, WaterChannelController *waterChannelController)
    : Task(period),
      waterChannelController(waterChannelController),
      lastMessage(0),
      messageReceiver(),
      messageSender(),
      jsonProcessor(jsonProcessor),
      messageAvailable(false),
      messageDelivered(0)
{
    Serial.begin(BAUD_RATE);
}
void SerialCommunicationTask::serialComm()
{
    String receivedContent;
    String status;
    String valveValue;
    if (Serial.available() > 0)
    {
        receivedContent = Serial.readStringUntil('\n');
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, receivedContent);
        if (error)
        {
            Serial.println("Failed to read JSON");
            return;
        }
        Serial.println(receivedContent);
        status = doc["status"].as<String>();

        if (status == "ALARM_TOO_LOW")
        {
            valveValue = "0";
        }
        else if (status == "NORMAL")
        {
            valveValue = "25";
        }
        else if (status == "PRE_ALARM_TOO_HIGH")
        {
            valveValue = "40";
        }
        else if (status == "ALARM_TOO_HIGH")
        {
            valveValue = "50";
        }
        else if (status == "ALARM_TOO_HIGH_CRITIC")
        {
            valveValue = "100";
        }
        else
        {
            valveValue = "unknown state";
        }

        // Creazione del documento JSON
        JsonDocument jsonDoc;
        jsonDoc["status"] = status;
        jsonDoc["valveValue"] = valveValue;

        // Serializzazione del documento JSON
        String output;
        serializeJson(jsonDoc, output);

        // Stampa il documento JSON sulla seriale
        Serial.println(output);
    }
}

void SerialCommunicationTask::tick()
{
    serialComm();
}
