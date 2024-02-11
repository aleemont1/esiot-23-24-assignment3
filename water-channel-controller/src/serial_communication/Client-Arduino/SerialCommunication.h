#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include "Arduino.h"
#include "ArduinoJson.h"
#include "JsonProcessor.h"
#include "MessageSender.h"
#include "MessageReceiver.h"

/**
 * @brief Manages a serial communication channel between a client and a server.
 *
 * The SerialCommunicationChannel class provides a high-level interface
 * for managing serial communication between a client (an Arduino board)
 * and a server (a computer).
 * It encapsulates the details of sending and receiving messages over a serial port,
 * and provides methods for processing received messages, checking message availability,
 * and closing the communication channel.
 *
 * Key responsibilities of this class include:
 * - Processing incoming messages and formatting outgoing messages.
 * - Managing the state of the communication channel (open, closed).
 * - Checking the availability of incoming messages.
 *
 * @note This class is specifically designed for communication where
 * the client is an Arduino board and the server is a computer.
 */
class SerialCommunicationChannel
{

public:
    /**
     * @brief Constructs a new SerialCommunicationChannel object.
     */
    SerialCommunicationChannel(JsonProcessor jsonProcessor);

    /**
     * @brief Uses RAII to automatically close the serial port when the object is destroyed.
     */
    ~SerialCommunicationChannel();

    /**
     * @brief Initializes the serial communication channel.
     *
     * This function sets up the serial communication with the Arduino board.
     * It should be called before any other serial communication functions are used.
     */
    void initializeSerialCommunication();

private:
    /**
     * @brief An instance of the JsonProcessor class.
     *
     * This instance, jsonProcessor, is used to handle JSON-formatted messages within the SerialCommunication class. It provides methods for processing these messages, including parsing the JSON content, extracting relevant information, and formatting it for use by other parts of the application.
     */
    JsonProcessor jsonProcessor;

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
     * @brief The baud rate used by the serial communication channel.
     */
    const int BAUD_RATE = 9600;

    /**
     * @brief The maximum amount of time to wait for data to be available on the serial port.
     *
     * This constant defines the maximum amount of time, in milliseconds, that the system
     * will wait for data to become available on the serial port before timing out.
     * It is used in the getReceivedContent method to control how long the method waits for incoming data.
     */
    const unsigned long WAIT_TIME = 500;

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
     * @brief Processes a specific end message received from the server
     * to close the communication channel.
     */
    void receivedEndMessage();

    /**
     * @brief an instance of the MessageSender class.
     */
    MessageSender messageSender;

    /**
     * @brief an instance of the MessageReceiver class.
     */
    MessageReceiver messageReceiver;
};

#endif // __COMMUNICATION_H__