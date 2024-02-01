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
    String valveValue = getValveValue(status);
    doc["valveValue"] = valveValue;

    String confirmationMessage;
    serializeJson(doc, confirmationMessage);

    return confirmationMessage;
}
String JsonProcessor::getValveValue(String status)
{
    if (status == "NORMAL")
        return "25";
    else if (status == "ALARM_TOO_LOW")
        return "0";
    else if (status == "PRE_ALARM_TOO_HIGH")
        return "40";
    else if (status == "ALARM_TOO_HIGH")
        return "50";
    else if (status == "ALARM_TOO_HIGH_CRITIC")
        return "100";
    else if (status == "ping")
        return "ping";
    else
        return "Unknown status";
}