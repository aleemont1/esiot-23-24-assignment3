#ifndef __JSONPROCESSOR_H__
#define __JSONPROCESSOR_H__

#include "Arduino.h"
#include "ArduinoJson.h"
#include "serial_communication/Client-Arduino/ValveController.h"

/**
 * @brief A utility class for handling JSON-formatted messages.
 *
 * The JsonProcessor class provides methods for processing JSON-formatted
 * messages received from a server.
 * It is responsible for parsing the JSON content, extracting relevant information,
 * and formatting it for use by other parts of the application.
 * This class is an essential part of the communication pipeline,
 * ensuring that incoming messages are correctly interpreted and handled.
 *
 */
class JsonProcessor
{
public:
    /**
     * @brief Constructs a new JsonProcessor object.
     */
    JsonProcessor();

    /**
     * @brief Processes a JSON-formatted message received from the server.
     *
     * This method is responsible for parsing and processing the content
     * of a message received from the server.
     * The message is expected to be in JSON format.
     * The method extracts relevant information from the JSON object
     * and formats it into a string that can be used by other parts
     * of the application.
     *
     * @param receivedContent A string representing the JSON-formatted
     * message received from the server.
     * @return String The processed message, extracted and formatted
     * from the original JSON content.
     */
    String processReceivedContent(String receivedContent);

    /**
     * @brief Constructs a confirmation message derived from the original message.
     *
     * This method is responsible for generating a confirmation message that
     * acknowledges the receipt and processing of the original message.
     * The confirmation message is constructed in a specific format that
     * is recognized by the receiving end.
     *
     * @param originalMessage The original message that was received and processed.
     * This is used as a basis for creating the confirmation message.
     * @return A String representing the confirmation message.
     * This message is ready to be sent back to the sender to confirm
     *  that the original message was successfully received and processed.
     */
    String createConfirmationMessage(String originalMessage);

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
     * @brief Extracts the status from the received content.
     *
     * @param receivedContent A string representing the JSON-formatted message received from the server.
     * @return String The status extracted from the received content.
     */
    String getSystemState(String receivedContent);

    /**
     * @brief Extracts the valve value from the received content.
     *
     * @param receivedContent A string representing the JSON-formatted message received from the server.
     * @return int The valve value extracted from the received content.
     */
    int getValveValue(String receivedContent);

private:
    ValveController valveController; ///< The valve controller object used to manage the valve.
};

#endif // __JSONPROCESSOR_H__
