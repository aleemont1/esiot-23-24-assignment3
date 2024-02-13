#include "ValveTask.h"
#include "components/api/ServoMotorImpl.h"

ValveTask::ValveTask(int period, WaterChannelController *waterChannelController, int servoPin)
    : TaskWithState(period), waterChannelController(waterChannelController), motor(new ServoMotorImpl(servoPin))
{
    this->motor->on();
    this->motor->setPosition(0);
    setState(ValveStates::Idle);
}

void ValveTask::tick()
{
    switch (this->getState())
    {
    case ValveStates::Idle:
        if (this->waterChannelController->posChange)
        {
            this->motor->setPosition(map((int)this->waterChannelController->activePosition, 0, 100, 0, 180));
            this->waterChannelController->posChange = false;
        }
        break;
    case ValveStates::Opening:
        if (this->elapsedTimeInState() > this->timeToMove)
        {
            this->setState(ValveStates::Idle);
        }
        break;
    default:
        break;
    }
}