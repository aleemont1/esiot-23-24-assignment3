#define DEBUG
#include "MessageSender.h"
#include "system/Logger.h"
#include "../Client-Arduino/ValveController.h"

MessageSender::MessageSender() {}

MessageSender::~MessageSender() {}

bool MessageSender::sendMessage(String message)
{
    // Send the message to the server
    size_t bytesSent = Serial.println(message);
    // logger("Sent message: " + message);
    // Check if the message is sent
    return checkMessageSent(bytesSent, message);
}

bool MessageSender::checkMessageSent(size_t bytesSent, String message)
{
    // If the message is sent, set the messageDelivered flag to true
    if (bytesSent == message.length())
    {
        setMessageDelivered(true);
        return true;
    }
    setMessageDelivered(false);
    return false;
}

void MessageSender::setMessageDelivered(bool messageDelivered)
{
    this->messageDelivered = messageDelivered;
}

void MessageSender::sentMessageConfirmation(String originalMessage)
{
    String confirmationMessage = jsonProcessor.createConfirmationMessage(originalMessage);
    sendMessage(confirmationMessage);
}