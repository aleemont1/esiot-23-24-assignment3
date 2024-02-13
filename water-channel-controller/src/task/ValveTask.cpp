#include "ValveTask.h"
#include "components/api/ServoMotorImpl.h"

ValveTask::ValveTask(int period, WaterChannelController *waterChannelController, int servoPin)
    : TaskWithState(period), waterChannelController(waterChannelController), motor(new ServoMotorImpl(servoPin))
{
    initializeMotor();
}

void ValveTask::tick()
{
    switch (getState())
    {
    case ValveStates::Idle:
        handleIdleState();
        break;
    case ValveStates::Opening:
        handleOpeningState();
        break;
    default:
        break;
    }
}

void ValveTask::initializeMotor()
{
    turnMotorOn();
    setMotorToMinAngle();
    transitionToIdleState();
}

void ValveTask::turnMotorOn()
{
    motor->on();
}

void ValveTask::setMotorToMinAngle()
{
    motor->setPosition(MIN_SERVO_ANGLE);
}

void ValveTask::transitionToIdleState()
{
    setState(ValveStates::Idle);
}

void ValveTask::handleIdleState()
{
    if (isPositionChanged())
    {
        updateMotorPosition();
        resetPositionChangeFlag();
    }
}

bool ValveTask::isPositionChanged()
{
    return waterChannelController->posChange;
}

void ValveTask::updateMotorPosition()
{
    int mappedPosition = map(static_cast<int>(waterChannelController->activePosition), MIN_POSITION_PERCENT, MAX_POSITION_PERCENT, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
    motor->setPosition(mappedPosition);
}

void ValveTask::resetPositionChangeFlag()
{
    waterChannelController->posChange = false;
}

void ValveTask::handleOpeningState()
{
    if (isTimeToMoveElapsed())
    {
        transitionToIdleState();
    }
}

bool ValveTask::isTimeToMoveElapsed()
{
    return elapsedTimeInState() > timeToMove;
}