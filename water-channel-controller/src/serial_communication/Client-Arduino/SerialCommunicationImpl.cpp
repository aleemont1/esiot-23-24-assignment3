#include "SerialCommunication.h"

SerialCommunicationChannel::SerialCommunicationChannel()
    : messageAvailable(false), messageDelivered(false) {}

SerialCommunicationChannel::~SerialCommunicationChannel()
{
    Serial.end();
}

void SerialCommunicationChannel::initializeSerialCommunication()
{
    Serial.begin(BAUD_RATE);
    checkMessageAvailability();
    getReceivedContent();
}

bool SerialCommunicationChannel::checkMessageSent(size_t bytesSent, String message)
{
    // return the number of bytes sent to the server
    return bytesSent == message.length();
}

bool SerialCommunicationChannel::sendMessage(String message)
{
    // Used to represent the size of message (object of type String) in bytes
    size_t bytesSent = Serial.println(message);

    // Check if all bytes were sent successfully to the server
    return checkMessageSent(bytesSent, message);
}

bool SerialCommunicationChannel::isMessageDelivered()
{
    return messageDelivered;
}

bool SerialCommunicationChannel::checkMessageAvailability()
{
    messageAvailable = Serial.available() > 0;
    setMessageAvailable(true);
    return messageAvailable;
}

/*
    @note:
    In this version, the method waits up to 500 milliseconds for a message to become available.
    If a message becomes available within this time, it reads the message, processes it,
    and sends a confirmation back to the server.
    If no message becomes available within 500 milliseconds, it prints an error message.
    This version of the method is non-blocking (delay() instead is not), meaning it won't delay
    other operations while waiting for a message to become available.
*/
String SerialCommunicationChannel::getReceivedContent()
{
    unsigned long startTime = millis();
    String receivedContent = "";

    while (millis() - startTime < WAIT_TIME)
    {
        if (checkMessageAvailability())
        {
            // Read the message from the serial port
            receivedContent = Serial.readStringUntil('\n');

            // Process the received message
            // receivedContent = processReceivedContent(receivedContent);

            // After reading, send a confirmation back to the server
            sentMessageConfirmation(receivedContent);

            // Exit the loop once the message is received
            break;
        }
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
    JsonDocument doc;

    // Extract the status from the JSON document
    String status = doc["status"];

    // Create a readable version of the JSON
    receivedContent = "Processed JSON: " + status;
    receivedEndMessage();
    return receivedContent;
}

void SerialCommunicationChannel::sentMessageConfirmation(String originalMessage)
{
    // Serial.println("Received message: " + originalMessage);
    // Parse the original message into a JsonDocument
    JsonDocument doc;
    deserializeJson(doc, originalMessage);

    // Extract the status from the JSON document
    String status = doc["status"];

    // Get the corresponding valve value
    String valveValue = getValveValue(status);
    doc["valveValue"] = valveValue;

    // Serialize the modified JSON document to a string
    String confirmationMessage;
    serializeJson(doc, confirmationMessage);

    // Send the confirmation message
    sendMessage(confirmationMessage);
}

String SerialCommunicationChannel::formatMessage(String status, String valveValue)
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

String SerialCommunicationChannel::getValveValue(String status)
{
    if (status == "NORMAL")
        return "25%";
    else if (status == "ALARM-TOO-LOW")
        return "0%";
    else if (status == "PRE-ALARM-TOO-HIGH")
        return "40%";
    else if (status == "ALARM-TOO-HIGH")
        return "50%";
    else if (status == "ALARM-TOO-HIGH-CRITIC")
        return "100%";
    else if (status == "ping")
        return "0%";
    else
        return "Unknown status";
}
