#include "Arduino.h"
#include "SerialCommunication.h"

SerialCommunicationChannel::SerialCommunicationChannel()
{
    initializeSerialCommunication();
    checkMessageAvailability();
    getReceivedContent();
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

String SerialCommunicationChannel::processReceivedContent(String receivedContent)
{
    if (receivedContent == "end")
    {
        receivedEndMessage();
        receivedContent = "";
    }
    return receivedContent;
}

void SerialCommunicationChannel::receivedEndMessage()
{
    sendMessage("status : " + status + " valveValue : " + valveValue);
}
