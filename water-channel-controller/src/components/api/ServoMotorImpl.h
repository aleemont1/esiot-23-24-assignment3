#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include "Arduino.h"
#include "ServoTimer2.h"

/**
 * @brief This class is a concrete implementation of the ServoMotor abstract class.
 *
 * The ServoMotorImpl class provides the specific implementation for a servo motor in an Arduino context.
 * It inherits from the ServoMotor abstract class and implements the on, off, and setPosition methods.
 */
class ServoMotorImpl : public ServoMotor
{
public:
    /**
     * @brief Construct a new ServoMotorImpl object.
     *
     * @param pin The Arduino pin number to which the servo motor is connected.
     */
    ServoMotorImpl(int pin);

    /**
     * @brief Turns the servo motor on.
     *
     * This method sends a signal to the servo motor to start moving.
     */
    void on() override;

    /**
     * @brief Turns the servo motor off.
     *
     * This method sends a signal to the servo motor to stop moving.
     */
    void off() override;

    /**
     * @brief Set the position of the servo motor in degrees.
     *
     * This method sends a signal to the servo motor to rotate to the specified position.
     *
     * @param angle The desired position of the servo motor in degrees. The valid range is from 0 to 180 degrees.
     */
    void setPosition(int angle) override;

private:
    int pin;                                     ///< The Arduino pin number to which the servo motor is connected.
    ServoTimer2 motor;                           ///< An instance of the ServoTimer2 class used to control the servo motor.
    const int MAX_ANGLE = 180;                   ///< The maximum angle that the servo motor can reach.
    const int MIN_ANGLE = 0;                     ///< The minimum angle that the servo motor can reach.
    const double SERVO_MAX_PULSE_WIDTH = 2400.0; ///< The maximum pulse width that the servo motor can reach.
    const double SERVO_MIN_PULSE_WIDTH = 544.0;  ///< The minimum pulse width that the servo motor can reach.
    const double SERVO_MAX_ANGLE = 180.0;        ///< The maximum angle that the servo motor can reach.
};

#endif // __SERVO_MOTOR_IMPL__