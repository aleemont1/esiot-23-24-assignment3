#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

/**
 * @brief This class represents a Servo Motor.
 *
 * The ServoMotor class is an abstract class that provides the basic functionalities of a servo motor.
 * A servo motor is a rotary actuator or linear actuator that allows for precise control of angular or linear position.
 * The class is designed to be inherited by specific implementations of servo motors.
 */
class ServoMotor
{
public:
    /**
     * @brief Turns the servo motor on.
     *
     * This is a pure virtual function, to be implemented by derived classes.
     */
    virtual void on() = 0;

    /**
     * @brief Turns the servo motor off.
     *
     * This is a pure virtual function, to be implemented by derived classes.
     */
    virtual void off() = 0;

    /**
     * @brief Set the position of the servo motor in degrees.
     *
     * This is a pure virtual function, to be implemented by derived classes.
     *
     * @param angle The desired position of the servo motor in degrees. The valid range is typically from 0 to 180 degrees, but can vary depending on the specific servo motor used.
     */
    virtual void setPosition(int angle) = 0;
};

#endif // __SERVO_MOTOR__