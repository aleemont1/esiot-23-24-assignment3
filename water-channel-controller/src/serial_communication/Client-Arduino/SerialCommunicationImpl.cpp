#include "Arduino.h"
#include "SerialCommunication.h"

SerialCommunicationChannel::SerialCommunicationChannel()
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
    Serial.begin(9600);
    messageAvailable = false;
    messageDelivered = false;
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
    String receivedContent = "";
    if (checkMessageAvailability())
    {
        setMessageAvailable(true);
        receivedContent = Serial.readStringUntil('\n'); // >TODO: test this
        receivedContent = processReceivedContent(receivedContent);
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
    if (isValidStatus(status) && isValidValveValue(valveValue))
    {
        String message = formatMessage(status, valveValue);
        sendMessage(message);
    }
}

String SerialCommunicationChannel::processReceivedContent(String receivedContent)
{
    if (receivedContent == "end")
    {
        receivedEndMessage();
        receivedContent = "";
    }
    return receivedContent;
}

bool SerialCommunicationChannel::isValidStatus(String status)
{
    // Assuming status can be "OK" or "ERROR"
    return status == "NORMAL" || status == "ALARM-TOO-LOW" ||
           status == "PRE-ALARM-TOO-HIGH" || status == "ALARM-TOO-HIGH" ||
           status == "ALARM-TOO-HIGH-CRITIC";
}

bool SerialCommunicationChannel::isValidValveValue(String valveValue)
{
    // Assuming valveValue is a number between 0 and 100
    int value = valveValue.toInt();
    return value >= 0 && value <= 100;
}

String SerialCommunicationChannel::formatMessage(String status, String valveValue)
{
    // Format the message as a JSON string
    return "{\"status\":\"" + status + "\",\"valveValue\":\"" + valveValue + "\"}";
}
