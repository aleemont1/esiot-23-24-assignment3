#ifndef __SERIALCOMM_H__
#define __SERIALCOMM_H__

#include "ArduinoJson.h"
#include "Arduino.h"

/**
 * @brief A class to handle serial communication.
 *
 * This class provides methods for creating responses and handling
 * serial communication. It is designed to be used with Arduino.
 */
class SerialComm
{
public:
    /**
     * @brief Creates a response string.
     *
     * This method takes a status string as input and returns a response string.
     * The exact format and content of the response string is determined by the implementation.
     *
     * @param status The status string to be included in the response.
     * @return A response string based on the input status.
     */
    String createResponse(String status);

    /**
     * @brief Handles serial communication.
     *
     * This method is responsible for managing the serial communication. It should be called
     * regularly to ensure that incoming data is processed and outgoing data is sent in a timely manner.
     */
    void serialCommunication();
};

#endif // __SERIALCOMM_H__