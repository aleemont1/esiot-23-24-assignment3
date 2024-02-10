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
    String valveValue = valveController.setValveValue(status);
    doc["valveValue"] = valveValue;

    String confirmationMessage;
    serializeJson(doc, confirmationMessage);

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

String JsonProcessor::getStatus(String receivedContent)
{
    JsonDocument doc;
    deserializeJson(doc, receivedContent);

    String status = doc["status"];
    return status;
}