#include "SerialCommunication.h"

SerialCommunicationChannel::SerialCommunicationChannel(JsonProcessor jsonProcessor)
    : jsonProcessor(jsonProcessor), messageAvailable(false), messageDelivered(false) {}

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

void SerialCommunicationChannel::sentMessageConfirmation(String originalMessage)
{
    String confirmationMessage = jsonProcessor.createConfirmationMessage(originalMessage);
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