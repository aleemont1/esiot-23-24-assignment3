#include "task/SerialCommunicationTask.h"

SerialCommunicationTask::SerialCommunicationTask(int period, JsonProcessor jsonProcessor, WaterChannelController *waterChannelController)
    : Task(period), jsonProcessor(jsonProcessor), waterChannelController(waterChannelController), messageAvailable(false), messageDelivered(false) {}

void SerialCommunicationTask::tick()
{
    initializeSerialCommunication();
    receivedEndMessage();
}

void SerialCommunicationTask::initializeSerialCommunication()
{
    Serial.begin(BAUD_RATE);
    messageReceiver.checkMessageAvailability();
    messageReceiver.getReceivedContent();
}

void SerialCommunicationTask::receivedEndMessage()
{
    String message = jsonProcessor.formatMessage(status, valveValue);
    messageSender.sendMessage(message);
}
