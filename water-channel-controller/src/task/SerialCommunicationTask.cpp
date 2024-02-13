#include "task/SerialCommunicationTask.h"
#include "system/Logger.h"
#define DEBUG

SerialCommunicationTask::SerialCommunicationTask(int period, JsonProcessor jsonProcessor, WaterChannelController *waterChannelController)
    : Task(period),
      waterChannelController(waterChannelController),
      lastMessage(0),
      messageReceiver(),
      messageSender(),
      jsonProcessor(jsonProcessor),
      messageAvailable(false),
      messageDelivered(0)
{
    Serial.begin(BAUD_RATE);
}

void SerialCommunicationTask::tick()
{
    messageReceiver.checkMessageAvailability();
    messageReceiver.getReceivedContent();
}