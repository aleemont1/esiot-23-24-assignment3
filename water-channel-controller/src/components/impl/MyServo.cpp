#include "../api/MyServo.h"

MyServo::MyServo(int pin) : pin(pin)
{
    servo.attach(pin);
}

void MyServo::setPosition(int angle)
{
    servo.write(angle);
}

void MyServo::detach()
{
    servo.detach();
}

bool MyServo::isValidAngle(int angle)
{
    return angle >= 0 && angle <= 180;
}

void MyServo::moveToAngleAtSpeed(int targetAngle, unsigned long speed)
{
    int currentAngle = servo.read();

    int step = currentAngle < targetAngle ? 1 : -1;

    unsigned long lastStepTime = millis();

    for (int angle = currentAngle; angle != targetAngle; angle += step)
    {
        if (millis() - lastStepTime >= speed)
        {
            servo.write(angle);
            lastStepTime = millis();
        }
    }
}