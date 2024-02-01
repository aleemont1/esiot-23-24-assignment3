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
    else if (status == "ALARM-TOO-LOW")
        return "0";
    else if (status == "PRE-ALARM-TOO-HIGH")
        return "40";
    else if (status == "ALARM-TOO-HIGH")
        return "50";
    else if (status == "ALARM-TOO-HIGH-CRITIC")
        return "100";
    else if (status == "ping")
        return "0";
    else
        return "Unknown status";
}