#ifndef __JSONPROCESSOR_H__
#define __JSONPROCESSOR_H__

#include <Arduino.h>
#include <ArduinoJson.h>

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
     * @brief Retrieves the corresponding valve value for a given status.
     *
     * This method maps the status of the system to a valve value.
     * The status is a string that represents the current state of the system,
     * and the valve value is a string that represents the percentage of the
     * valve that should be open in response to the current status.
     *
     * @param status A string representing the current status of the system.
     *
     * @return String The corresponding valve value as a string representing a percentage.
     * For example, "25%" for a normal status, "0%" for an alarm-too-low status, etc.
     * If the status is unknown, it returns "Unknown status".
     */
    String getValveValue(String status);
};

#endif // __JSONPROCESSOR_H__
