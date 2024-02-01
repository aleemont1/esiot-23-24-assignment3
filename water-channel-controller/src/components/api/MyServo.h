#ifndef __MYSERVO_H__
#define __MYSERVO_H__

#include "Arduino.h"
#include "ServoTimer2.h"

/**
 * @brief This class provides an interface for controlling a servo motor.
 *
 * The Servo class uses the ServoTimer2 library to control a servo motor
 * connected to an Arduino board. The class provides methods to set the
 * servo to a specific angle and to detach the servo, stopping it from moving.
 */
class MyServo
{
public:
    /**
     * @brief Construct a new Servo object.
     *
     * @param pin The pin number on the Arduino board to which the servo motor is connected.
     * This pin number is used to control the servo motor via PWM signal.
     */
    MyServo(int pin);

    /**
     * @brief Set the servo motor to a specific angle.
     *
     * This method sends a PWM signal to the servo motor to move it to a specific angle.
     * The angle is specified in degrees, with 0 degrees meaning the servo is at its
     * minimum position and 180 degrees meaning the servo is at its maximum position.
     *
     * @param angle The angle to set the servo motor to, between 0 and 180 degrees.
     */
    void write(int angle);

    /**
     * @brief Detach the servo motor, stopping it from moving.
     *
     * This method stops sending PWM signals to the servo motor, effectively stopping
     * it from moving. This can be useful to reduce power consumption when the servo
     * motor is not in use.
     */
    void detach();

    /**
     * @brief Validate the angle for the servo motor.
     *
     * This method checks if the provided angle is within the valid range for a servo motor,
     * which is between 0 and 180 degrees.
     *
     * @param angle The angle to validate.
     * @return true if the angle is valid, false otherwise.
     */
    bool isValidAngle(int angle);

    /**
     * @brief Move the servo to a specific angle at a certain speed.
     *
     * This method gradually changes the angle of the servo over a period of time,
     * simulating the effect of moving at a certain speed. The speed of the movement
     * is controlled by adjusting the time interval between each 1 degree step.
     *
     * @note This method uses the millis() function to control the speed of the movement,
     * which allows other code to run in between steps. This makes the program more responsive
     * compared to using the delay() function.
     *
     * @param targetAngle The target angle to move the servo to, between 0 and 180 degrees.
     * @param speed The speed at which to move the servo. This is the time in milliseconds
     * between each 1 degree step. A lower value will result in a faster movement.
     */
    void moveToAngleAtSpeed(int targetAngle, unsigned long speed);

private:
    ServoTimer2 servo; ///< An instance of the ServoTimer2 class used to control the servo motor.
    int pin;           ///< The pin number on the Arduino board to which the servo motor is connected.
};

#endif // __MYSERVO_H__
