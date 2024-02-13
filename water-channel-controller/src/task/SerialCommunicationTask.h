#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_H__

#include "WaterChannelController.h"
#include "system/Task.h"
#include "serial_communication/Client-Arduino/JsonProcessor.h"
#include "serial_communication/Client-Arduino/MessageReceiver.h"
#include "serial_communication/Client-Arduino/MessageSender.h"
#include "Arduino.h"

class SerialCommunicationTask : public Task
{
public:
    SerialCommunicationTask(int period, JsonProcessor jsonProcessor, WaterChannelController *waterChannelController);
    void initializeSerialCommunication();
    void receivedEndMessage();
    void tick() override;

private:
    WaterChannelController *waterChannelController;
    unsigned long int lastMessage{0};
    MessageReceiver messageReceiver;
    MessageSender messageSender;
    JsonProcessor jsonProcessor;
    const int BAUD_RATE = 9600;
    String status;
    String valveValue;
    String content;
    bool messageAvailable;
    bool messageDelivered;
};

#endif // __SERIAL_COMMUNICATION_H__
