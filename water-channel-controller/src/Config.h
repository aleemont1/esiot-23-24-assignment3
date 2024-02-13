#ifndef __CONFIG__
#define __CONFIG__
#define __DEBUG__

#include "Arduino.h"

constexpr int BASE_PERIOD = 100;
constexpr int POT_PIN = A0;
constexpr int BUTTON_PIN = 4;
constexpr long TIME_OUT_CONNECTION = 300000L;
constexpr int SERVO_PIN = 9;
constexpr int TIME_TO_MOVE = 20;

#endif // __CONFIG__