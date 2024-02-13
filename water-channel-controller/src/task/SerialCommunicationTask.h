#ifndef __SERIAL_COMMUNICATION_H__
#define __SERIAL_COMMUNICATION_H__

#include "WaterChannelController.h"
#include "system/Task.h"
#include "serial_communication/Client-Arduino/JsonProcessor.h"
#include "serial_communication/Client-Arduino/MessageReceiver.h"
#include "serial_communication/Client-Arduino/MessageSender.h"
#include "system/Logger.h"
#include "../components/api/ServoMotor.h"
#include "Arduino.h"

class SerialCommunicationTask : public Task
{
public:
    SerialCommunicationTask(int period, JsonProcessor jsonProcessor, WaterChannelController *waterChannelController);
    void initializeSerialCommunication();
    void receivedEndMessage();
    String formatMessage(String status, String valveValue);
    String createConfirmationMessage(String originalMessage);
    String getSystemStatus(String receivedMessage);
    void tick() override;

private:
    unsigned long BAUD_RATE = 9600;
    WaterChannelController *waterChannelController;
    unsigned long int lastMessage{0};
    MessageReceiver messageReceiver;
    MessageSender messageSender;
    JsonProcessor jsonProcessor;
    String status;
    String valveValue;
    String content;
    bool messageAvailable;
    bool messageDelivered;
    ServoMotor *motor; ///< The ServoMotor used to control the valve.
};

#endif // __SERIAL_COMMUNICATION_H__
