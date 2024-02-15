#include "JsonProcessor.h"

JsonProcessor::JsonProcessor() {}

String JsonProcessor::processReceivedContent(String receivedContent)
{
    JsonDocument doc;
    deserializeJson(doc, receivedContent);

    String status = doc["status"];
    String formattedContent = "Processed JSON: " + status;

    return formattedContent;
}

String JsonProcessor::createConfirmationMessage(String originalMessage)
{
    JsonDocument doc;
    deserializeJson(doc, originalMessage);

    String status = doc["status"];
    String valveValue = valveController.getValveValueForState(status);

    JsonDocument confirmationDoc;

    if (valveValue != "unknown state")
    {
        confirmationDoc["status"] = status;
        confirmationDoc["valveValue"] = valveValue;
    }
    else
    {
        confirmationDoc["valveValue"] = "unknown state";
    }

    String confirmationMessage;
    serializeJson(confirmationDoc, confirmationMessage);

    return confirmationMessage;
}

String JsonProcessor::formatMessage(String status, String valveValue)
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

String JsonProcessor::getSystemState(String receivedContent)
{
    JsonDocument doc;
    deserializeJson(doc, receivedContent);

    String status = doc["status"];
    return status;
}

int JsonProcessor::getValveValue(String receivedContent)
{
    JsonDocument doc;
    deserializeJson(doc, receivedContent);

    String valveValue = doc["valveValue"];
    int valveValueInt = valveValue.toInt(); // Convert string to integer
    return valveValueInt;
}