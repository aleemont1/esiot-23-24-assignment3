#ifndef __MESSAGERECEIVER_H__
#define __MESSAGERECEIVER_H__

#include "Arduino.h"
#include "MessageSender.h"

/**
 * @brief Responsible for receiving messages over the serial port.
 *
 * The MessageReceiver class provides methods to check if a message is available on the serial port,
 * retrieve the content of the most recently received message, and set the availability status of messages.
 */
class MessageReceiver
{
public:
    /**
     * @brief Construct a new Message Receiver object.
     */
    MessageReceiver();

    /**
     * @brief Destroy the Message Receiver object.
     */
    ~MessageReceiver();

    /**
     * @brief Retrieves the content of the most recently received message.
     *
     * @return String The content of the message received from the server.
     */
    String getReceivedContent();

    /**
     * @brief Checks if a message is available on the serial port to be read by the client.
     *
     * @return bool True if a message is available, false otherwise.
     */
    bool checkMessageAvailability();

    /**
     * @brief Sets the availability status of messages on the serial port.
     *
     * @param status The availability status of the message.
     * True if a message is available, false otherwise.
     */
    void setMessageAvailable(bool messageAvailable);

    /**
     * @brief Checks if a message is available on the serial port to be read by the client.
     *
     * @return bool True if a message is available, false otherwise.
     */
    bool isMessageAvailable();

private:
    /**
     * @brief A flag indicating whether a message is available
     * on the serial port to be read by the client.
     */
    bool messageAvailable;

    /**
     * @brief An instance of the MessageSender class.
     */
    MessageSender messageSender;

    /**
     * @brief The maximum amount of time to wait for data to be available on the serial port.
     *
     * This constant defines the maximum amount of time, in milliseconds, that the system
     * will wait for data to become available on the serial port before timing out.
     * It is used in the getReceivedContent method to control how long the method waits for incoming data.
     */
    const unsigned long WAIT_TIME = 500;
};

#endif // __MESSAGERECEIVER_H__