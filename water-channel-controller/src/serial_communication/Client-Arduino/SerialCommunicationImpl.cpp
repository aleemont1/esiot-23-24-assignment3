#include "Arduino.h"
#include "SerialCommunication.h"

SerialCommunicationChannel::SerialCommunicationChannel()
    : messageAvailable(false), messageDelivered(false)
{
    initializeSerialCommunication();
    checkMessageAvailability();
    getReceivedContent();
}

SerialCommunicationChannel::~SerialCommunicationChannel()
{
    Serial.end();
}

void SerialCommunicationChannel::initializeSerialCommunication()
{

    Serial.begin(BAUD_RATE);
}

void SerialCommunicationChannel::sendMessage(String message)
{
    Serial.println(message);
    isMessageDelivered();
}

bool SerialCommunicationChannel::isMessageDelivered()
{
    return messageDelivered;
}

void SerialCommunicationChannel::sendEndMessage(String endMessage)
{
    sendMessage(endMessage);
}

bool SerialCommunicationChannel::checkMessageAvailability()
{
    messageAvailable = Serial.available() > 0;
    return messageAvailable;
}

String SerialCommunicationChannel::getReceivedContent()
{
    delay(500);
    String receivedContent = "";
    if (checkMessageAvailability())
    {
        // Read the message from the serial port
        receivedContent = Serial.readStringUntil('\n');

        // // Process the received message
        // receivedContent = processReceivedContent(receivedContent);

        // After reading, send a confirmation back to the server
        sentMessageConfirmation(receivedContent);
    }
    return receivedContent;
}

void SerialCommunicationChannel::setMessageAvailable(bool messageAvailable)
{
    this->messageAvailable = messageAvailable;
}

bool SerialCommunicationChannel::isMessageAvailable()
{
    return messageAvailable;
}

void SerialCommunicationChannel::setMessageDelivered(bool messageDelivered)
{
    this->messageDelivered = messageDelivered;
}

void SerialCommunicationChannel::receivedEndMessage()
{
    String message = formatMessage(status, valveValue);
    sendMessage(message);
}

String SerialCommunicationChannel::processReceivedContent(String receivedContent)
{
    receivedContent = "";
    // Create a DynamicJsonDocument with a capacity of 1024 bytes
    DynamicJsonDocument doc(1024);

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, receivedContent);

    // Test if parsing succeeds.
    if (error)
    {
        return "deserializeJson() failed: " + String(error.c_str());
    }

    // Extract the status from the JSON document
    String status = doc["status"];

    // Create a readable version of the JSON
    receivedContent = "Processed JSON: " + status;

    receivedEndMessage();

    return receivedContent;
}

void SerialCommunicationChannel::sentMessageConfirmation(String originalMessage)
{
    // Write on the serial line the confirmation of the receipt
    Serial.println("Received message: " + originalMessage);

    // Create a DynamicJsonDocument with a capacity of 1024 bytes
    DynamicJsonDocument doc(1024);

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, originalMessage);

    // Test if parsing succeeds.
    if (error)
    {
        Serial.println("deserializeJson() failed: " + String(error.c_str()));
        return;
    }

    // Extract the status from the JSON document
    String status = doc["status"];

    // Get the corresponding valve value
    String valveValue;
    if (status == "NORMAL")
        valveValue = "25%";
    else if (status == "ALARM-TOO-LOW")
        valveValue = "0%";
    else if (status == "PRE-ALARM-TOO-HIGH")
        valveValue = "40%";
    else if (status == "ALARM-TOO-HIGH")
        valveValue = "50%";
    else if (status == "ALARM-TOO-HIGH-CRITIC")
        valveValue = "100%";
    else if (status == "ping")
        valveValue = "0%";
    else
        valveValue = "Unknown status";

    // Create a confirmation message
    // DynamicJsonDocument confirmationDoc(1024);
    // confirmationDoc["confirmation"] = "Received";
    // confirmationDoc["status"] = status;
    // confirmationDoc["valveValue"] = valveValue;

    doc["valveValue"] = valveValue;

    // Serialize JSON document to string
    String confirmationMessage;
    serializeJson(doc, confirmationMessage);

    // Send the confirmation message
    sendMessage(confirmationMessage);
}

String SerialCommunicationChannel::formatMessage(String status, String valveValue)
{
    // Format the message as a JSON string
    return "{\"status\":\"" + status + "\",\"valveValue\":\"" + valveValue + "\"}";
}
