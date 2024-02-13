#include "MessageReceiver.h"

MessageReceiver::MessageReceiver()
    : messageAvailable(false) {}

MessageReceiver::~MessageReceiver() {}

String MessageReceiver::getReceivedContent()
{
    // unsigned long startTime = millis();
    String receivedContent = "";

    // while (millis() - startTime < WAIT_TIME)
    // {
    if (checkMessageAvailability())
    {
        // Read the message from the serial port
        receivedContent = Serial.readStringUntil('\n');

        // After reading, send a confirmation back to the server
        messageSender.sentMessageConfirmation(receivedContent);

        // Exit the loop once the message is received
        // break;
    }
    // }

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
