#include "../api/ServoMotorImpl.h"

ServoMotorImpl::ServoMotorImpl(int pin) : pin(pin) {}

void ServoMotorImpl::on()
{
    motor.attach(pin);
}

void ServoMotorImpl::off()
{
    motor.detach();
}

void ServoMotorImpl::setPosition(int angle)
{
    if (angle > MAX_ANGLE)
    {
        angle = MAX_ANGLE;
    }
    else if (angle < MIN_ANGLE)
    {
        angle = MIN_ANGLE;
    }

    double coeff = (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH) / SERVO_MAX_ANGLE;
    motor.write((int)(SERVO_MIN_PULSE_WIDTH + angle * coeff));
}