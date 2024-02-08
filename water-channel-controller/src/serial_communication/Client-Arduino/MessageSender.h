#ifndef __MESSAGESENDER_H__
#define __MESSAGESENDER_H__

#include "Arduino.h"
#include "JsonProcessor.h"

/**
 * @brief Responsible for sending messages over the serial port.
 *
 * The MessageSender class provides methods to send messages to the server,
 * verify if the entire message was successfully sent, and send a confirmation
 * message in response to the original message received.
 */
class MessageSender
{
public:
    /**
     * @brief Construct a new Message Sender object.
     *
     */
    MessageSender();

    /**
     * @brief Destroy the Message Sender object.
     *
     */
    ~MessageSender();

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

private:
    /**
     * @brief A flag indicating whether my message has been
     * delivered to the server.
     */
    bool messageDelivered;

    /**
     * @brief an instance of the JsonProcessor class.
     *
     */
    JsonProcessor jsonProcessor;
};

#endif // __MESSAGESENDER_H__