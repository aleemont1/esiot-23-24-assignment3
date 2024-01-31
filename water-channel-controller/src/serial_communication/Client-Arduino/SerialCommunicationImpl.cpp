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
    // Check if all bytes were sent successfully
    if (bytesSent == message.length())
    {
        return true;
    }
    // If we reach this point, not all bytes were sent
    // Serial.println("Error: Not all bytes were sent to the server.");
    return false;
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

    while (millis() - startTime < 500)
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
    // Serial.println(String("Message availability set to: ") + (messageAvailable ? "Yes" : "No"));
}

bool SerialCommunicationChannel::isMessageAvailable()
{
    bool available = messageAvailable;
    // Serial.println(String("Message availability: ") + (available ? "Yes" : "No"));
    return available;
}

void SerialCommunicationChannel::setMessageDelivered(bool messageDelivered)
{
    this->messageDelivered = messageDelivered;
    // Serial.println(String("Message delivery status set to: ") + (messageDelivered ? "Delivered" : "Not Delivered"));
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
    JsonDocument doc;

    // Deserialize the JSON document
    // DeserializationError error = deserializeJson(doc, receivedContent);

    // // Extract the status from the JSON document
    // if (!doc.containsKey("status"))
    // {
    //     return "Error: JSON does not contain 'status' field.";
    // }

    // // Test if parsing succeeds.
    // if (error)
    // {
    //     return "deserializeJson() failed: " + String(error.c_str());
    // }

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
    JsonDocument doc;

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

    doc["valveValue"] = valveValue;

    // Serialize JSON document to string
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
