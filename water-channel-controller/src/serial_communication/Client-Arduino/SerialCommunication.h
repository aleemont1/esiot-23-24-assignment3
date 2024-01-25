#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include "Arduino.h"
#include "ArduinoJson.h"

/**
 * @brief This class represents a communication channel between a client
 * and a server over a serial port.
 *
 * It defines methods for processing received messages, sending messages,
 * checking if a message is available, and closing the communication channel.
 *
 * @note The client in this case is an Arduino board and the server is a computer.
 */
class SerialCommunicationChannel
{

public:
    /**
     * @brief Constructs a new SerialCommunicationChannel object.
     */
    SerialCommunicationChannel();

    /**
     * @brief Retrieves the content of the most recently received message.
     *
     * @return String The content of the message received from the server.
     */
    String getReceivedContent();

    /**
     * @brief Sets the availability status of messages on the serial port.
     *
     * @param status The availability status of the message.
     * True if a message is available, false otherwise.
     */
    void setMessageAvailable(bool status);

    /**
     * @brief Checks if a message is available on the serial port to be read by the client.
     *
     *
     * @return bool True if a message is available, false otherwise.
     */
    bool isMessageAvailable();

    /**
     * Sets the flag indicating whether the message has been delivered.
     *
     * @param messageDelivered True if the message has been delivered, false otherwise.
     */
    void setMessageDelivered(bool messageDelivered);

    /**
     * @brief Checks if my message is sended to the server.
     *
     * @return bool True if the message is sent, false otherwise.
     */
    bool isMessageDelivered();

private:
    /**
     * @brief The status of the valve received from the server.
     *
     * The valve's status depends on the received message.
     */
    String status;

    /**
     * @brief The valve value received from the server.
     *
     * This value is used to control the valve's opening and closing percentage.
     */
    String valveValue;

    /**
     * @brief The content of the message received from the server.
     */
    String content;

    /**
     * @brief A flag indicating whether a message is available
     * on the serial port to be read by the client.
     */
    bool messageAvailable;

    /**
     * @brief A flag indicating whether my message has been
     * delivered to the server.
     */
    bool messageDelivered;

    /**
     * @brief Processes a message received from the server.
     *
     * @param receivedContent The message received from the server.
     * @return String The processed message.
     */
    String processReceivedContent(String receivedContent);

    /**
     * @brief Processes a specific end message received from the server
     * to close the communication channel.
     */
    void receivedEndMessage();

    /**
     * @brief Sends a message to the server.
     *
     * @param message The message to send to the server.
     */
    void sendMessage(String message);

    /**
     * @brief Sends a specific end message to the server to close
     * the communication channel.
     *
     * @param endMessage The message to send to the server to end the communication.
     */
    void sendEndMessage(String endMessage);

    /**
     * @brief Checks if a message is available on the serial port to be read by the client.
     *
     * @return bool True if a message is available, false otherwise.
     */
    bool checkMessageAvailability();

    /**
     * @brief Initializes the serial communication channel.
     *
     * This function sets up the serial communication with the Arduino board.
     * It should be called before any other serial communication functions are used.
     */
    void initializeSerialCommunication();
};

#endif // __COMMUNICATION_H__