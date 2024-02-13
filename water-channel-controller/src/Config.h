#ifndef CONFIG_H
#define CONFIG_H

#include "Arduino.h"

/**
 * @brief Configuration file for the system.
 *
 * This file contains all the constant configuration values used throughout the system.
 */

/**
 * @brief The base period for tasks in milliseconds.
 */
constexpr int BASE_PERIOD = 100;

/**
 * @brief The analog pin connected to the potentiometer.
 */
constexpr int POT_PIN = A0;

/**
 * @brief The digital pin connected to the button.
 */
constexpr int BUTTON_PIN = 4;

/**
 * @brief The timeout for the connection in milliseconds.
 */
constexpr long TIME_OUT_CONNECTION = 300000L;

/**
 * @brief The digital pin connected to the servo motor.
 */
constexpr int SERVO_PIN = 9;

/**
 * @brief The time to move the servo motor in milliseconds.
 */
constexpr int TIME_TO_MOVE = 20;

#endif // CONFIG_H