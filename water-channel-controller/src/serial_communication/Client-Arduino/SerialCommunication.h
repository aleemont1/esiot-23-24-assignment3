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
     * @brief Uses RAII to automatically close the serial port when the object is destroyed.
     */
    ~SerialCommunicationChannel();

    /**
     * @brief Retrieves the content of the most recently received message.
     *
     * @return String The content of the message received from the server.
     */
    String getReceivedContent();

    /**
     * @brief Initializes the serial communication channel.
     *
     * This function sets up the serial communication with the Arduino board.
     * It should be called before any other serial communication functions are used.
     */
    void initializeSerialCommunication();

    /**
     * @brief Sets the availability status of messages on the serial port.
     *
     * @param status The availability status of the message.
     * True if a message is available, false otherwise.
     */
    void setMessageAvailable(bool status);

    /**
     * Sets the flag indicating whether the message has been delivered.
     *
     * @param messageDelivered True if the message has been delivered, false otherwise.
     */
    void setMessageDelivered(bool messageDelivered);

    /**
     * @brief Checks if a message is available on the serial port to be read by the client.
     *
     *
     * @return bool True if a message is available, false otherwise.
     */
    bool isMessageAvailable();

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
     * @brief The baud rate used by the serial communication channel.
     */
    const int BAUD_RATE = 9600;

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
     * @brief Sends a confirmation message in response to the original message received.
     *
     * This function is responsible for acknowledging the receipt and successful processing
     * of the original message sent by the client Arduino.
     * It does this by sending a confirmation message back to the client.
     * The confirmation message includes the status from the original message
     * and a corresponding valve value.
     * The valve value is determined based on the status received in the original message.
     *
     * The function performs the following steps:
     * 1. Echoes the original message back to the client as a form of receipt confirmation.
     * 2. Deserializes the original message to extract the "status" field.
     * 3. Determines the corresponding valve value based on the received status.
     * 4. Creates a new JSON document that includes the received status and the determined valve value.
     * 5. Serializes the new JSON document into a string.
     * 6. Sends the serialized string as the confirmation message back to the client.
     *
     * @param originalMessage The original message that was received from the client Arduino.
     */
    void sentMessageConfirmation(String originalMessage);

    /**
     * @brief Processes a specific end message received from the server
     * to close the communication channel.
     */
    void receivedEndMessage();

    /**
     * Formats the status and valve value into a structured message for transmission.
     *
     * This method takes the status of the water channel and the valve value as inputs,
     * and formats them into a structured message (e.g., a JSON string).
     * This formatted message can then be sent over the serial communication channel
     * to the Arduino.
     *
     * @param status A string representing the status of the water channel.
     * @param valveValue A string representing the value of the valve.
     * This should be a numeric value between 0 and 100, inclusive,
     * where 0 represents a fully closed valve
     * and 100 represents a fully open valve.
     * @return String A String containing the formatted message.
     * The format of this message could be a JSON string like
     * `{"status":"NORMAL","valveValue":"25"}`.
     */
    String formatMessage(String status, String valveValue);

    /**
     * @brief Checks if my message is sended to the server.
     *
     * @return bool True if the message is sent, false otherwise.
     */
    bool isMessageDelivered();

    /**
     * @brief Sends a message to the server and checks if it was sent successfully.
     *
     * This function sends a message to the server using the Serial.println() function.
     * After sending the message, it checks if the entire message was successfully
     * sent by comparing the number of bytes sent with the length of the message.
     * If all bytes were sent successfully, the function returns true.
     * If not all bytes were sent, it returns false.
     *
     * @param message The message to send to the server.
     * @return bool Returns true if the entire message was successfully sent,
     * false otherwise.
     */
    bool sendMessage(String message);

    /**
     * @brief Verifies if the entire message was successfully sent to the server.
     *
     * This function checks if the number of bytes sent to the server matches
     * the length of the message.
     * If the number of bytes sent and the message length are equal,
     * it means the entire message was successfully sent.
     * If they are not equal, it indicates that there was an error
     * and not all bytes of the message were sent.
     *
     * @param bytesSent The number of bytes that were sent to the server.
     * This is returned by the function used to send the message.
     * @param message The original message that was attempted to be sent to the server.
     * This is used to compare its length with the number of bytes sent.
     * @return bool Returns true if the entire message was successfully sent
     * (i.e., the number of bytes sent equals the message length), false otherwise.
     */
    bool checkMessageSent(size_t bytesSent, String message);

    /**
     * @brief Checks if a message is available on the serial port to be read by the client.
     *
     * @return bool True if a message is available, false otherwise.
     */
    bool checkMessageAvailability();
};

#endif // __COMMUNICATION_H__