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

void SerialCommunicationTask::tick()
{
    unsigned long startTime = millis();
    String receivedContent = "";
    while (millis() - startTime < 600)
    {
        logger("Checking message availability");
        if (Serial.available() > 0)
        {
            logger("Message available");
            messageAvailable = true;
            String message = Serial.readStringUntil('\n');
            JsonDocument doc;
            deserializeJson(doc, message);
            String status = doc["status"];         // This will hold the status value from the server
            String valveValue = doc["valveValue"]; // Get valveValue as a string
            // int valveValueInt = valveValue.toInt(); // Convert valveValue to an integer

            // Log the status and valveValue:
            // logger("Status: " + status);
            // logger("Valve Value: " + valveValue);
            // logger("Valve Value Int: " + String(valveValueInt));

            // Create a confirmation message and send it back:
            String confirmationMessage = createConfirmationMessage(message);

            break;
        }
    }
}

String SerialCommunicationTask::formatMessage(String status, String valveValue)
{
    JsonDocument doc;
    // Set the values in the JSON document
    doc["status"] = status;
    doc["valveValue"] = valveValue;

    // Serialize JSON document to string
    String formattedMessage;
    serializeJson(doc, formattedMessage);

    return formattedMessage;
}

String SerialCommunicationTask::createConfirmationMessage(String originalMessage)
{
    JsonDocument doc;
    deserializeJson(doc, originalMessage);

    String status = doc["status"];
    String valveValue = doc["valveValue"];
    // this->motor->setPosition(valveValue.toInt()); // Set the valve position to the value received from the server

    String confirmationMessage;
    serializeJson(doc, confirmationMessage);

    return confirmationMessage;
}

String SerialCommunicationTask::getSystemStatus(String receivedMessage)
{
    JsonDocument doc;
    deserializeJson(doc, receivedMessage);

    String status = doc["status"];
    return status;
}
