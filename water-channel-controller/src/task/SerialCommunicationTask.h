#ifndef __SERIAL_COMMUNICATION_TASK_
#define __SERIAL_COMMUNICATION_TASK_

#include "WaterChannelController.h"
#include "system/Task.h"
#include "serial_communication/Client-Arduino/JsonProcessor.h"
#include "serial_communication/Client-Arduino/MessageReceiver.h"
#include "serial_communication/Client-Arduino/MessageSender.h"
#include "system/Logger.h"
#include "../components/api/ServoMotor.h"
#include "Arduino.h"

/**
 * @brief Handles the serial communication tasks of the system.
 *
 * This class is responsible for handling all the serial communication tasks of the system. It extends the Task class and overrides the tick method.
 * It also provides methods to initialize serial communication, handle received end messages, format messages, create confirmation messages, and get system status.
 */
class SerialCommunicationTask : public Task
{
public:
    /**
     * @brief Construct a new Serial Communication Task object
     *
     * @param period The period of the task.
     * @param jsonProcessor The JsonProcessor object used for processing JSON messages.
     * @param waterChannelController Pointer to the WaterChannelController object.
     */
    SerialCommunicationTask(int period, JsonProcessor jsonProcessor, WaterChannelController *waterChannelController);

    /**
     * @brief Initializes serial communication.
     */
    void initializeSerialCommunication();

    /**
     * @brief Handles received end messages.
     */
    void receivedEndMessage();

    /**
     * @brief Formats a message with the given status and valve value.
     *
     * @param status The status to include in the message.
     * @param valveValue The valve value to include in the message.
     * @return String The formatted message.
     */
    String formatMessage(String status, String valveValue);

    /**
     * @brief Creates a confirmation message based on the original message.
     *
     * @param originalMessage The original message to base the confirmation message on.
     * @return String The confirmation message.
     */
    String createConfirmationMessage(String originalMessage);

    /**
     * @brief Gets the system status based on the received message.
     *
     * @param receivedMessage The received message to base the system status on.
     * @return String The system status.
     */
    String getSystemStatus(String receivedMessage);

    /**
     * @brief Overridden tick method from the Task class.
     */
    void tick() override;

private:
    unsigned long BAUD_RATE = 9600;                 ///< The baud rate for serial communication.
    WaterChannelController *waterChannelController; ///< Pointer to the WaterChannelController object.
    unsigned long int lastMessage{0};               ///< The last message received.
    MessageReceiver messageReceiver;                ///< The MessageReceiver object used for receiving messages.
    MessageSender messageSender;                    ///< The MessageSender object used for sending messages.
    JsonProcessor jsonProcessor;                    ///< The JsonProcessor object used for processing JSON messages.
    String status;                                  ///< The current status of the system.
    String valveValue;                              ///< The current valve value of the system.
    String content;                                 ///< The content of the current message.
    bool messageAvailable;                          ///< Flag to indicate if a message is available.
    bool messageDelivered;                          ///< Flag to indicate if a message has been delivered.
    ServoMotor *motor;                              ///< The ServoMotor used to control the valve.
};

#endif // __SERIAL_COMMUNICATION_TASK_