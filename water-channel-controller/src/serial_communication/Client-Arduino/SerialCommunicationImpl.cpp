// #include "SerialCommunication.h"

// SerialCommunicationChannel::SerialCommunicationChannel(JsonProcessor jsonProcessor)
//     : jsonProcessor(jsonProcessor), messageAvailable(false), messageDelivered(false) {}

// SerialCommunicationChannel::~SerialCommunicationChannel()
// {
//     Serial.end();
// }

// void SerialCommunicationChannel::initializeSerialCommunication()
// {
//     Serial.begin(BAUD_RATE);
//     messageReceiver.checkMessageAvailability();
//     messageReceiver.getReceivedContent();
// }

// void SerialCommunicationChannel::receivedEndMessage()
// {
//     String message = jsonProcessor.formatMessage(status, valveValue);
//     messageSender.sendMessage(message);
// }