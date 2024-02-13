#ifndef __LOGGER__
#define __LOGGER__

#include "Arduino.h"

/**
 * @brief Logs a string message.
 *
 * This function logs a string message to the console or other output device.
 *
 * @param log The string message to log.
 */
void logger(String log);

/**
 * @brief Logs a double value.
 *
 * This function logs a double value to the console or other output device. The value is converted to a string before logging.
 *
 * @param log The double value to log.
 */
void logger(double log);

/**
 * @brief Logs an integer value.
 *
 * This function logs an integer value to the console or other output device. The value is converted to a string before logging.
 *
 * @param log The integer value to log.
 */
void logger(int log);

#endif // __LOGGER__