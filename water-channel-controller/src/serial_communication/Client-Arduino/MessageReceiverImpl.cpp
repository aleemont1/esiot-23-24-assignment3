#include "MessageReceiver.h"

MessageReceiver::MessageReceiver()
    : messageAvailable(false) {}

MessageReceiver::~MessageReceiver() {}

String MessageReceiver::getReceivedContent()
{
    String receivedContent = "";

    if (checkMessageAvailability())
    {
        // Read the message from the serial port
        receivedContent = Serial.readStringUntil('\n');

        // After reading, send a confirmation back to the server
        messageSender.sentMessageConfirmation(receivedContent);
    }
    return receivedContent;
}

bool MessageReceiver::checkMessageAvailability()
{
    messageAvailable = Serial.available() > 0;
    setMessageAvailable(true);
    return messageAvailable;
}

void MessageReceiver::setMessageAvailable(bool messageAvailable)
{
    this->messageAvailable = messageAvailable;
}

bool MessageReceiver::isMessageAvailable()
{
    return messageAvailable;
}
