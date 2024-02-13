#ifndef __VALVE_TASK__
#define __VALVE_TASK__

#include "WaterChannelController.h"
#include "../components/api/ServoMotor.h"
#include "system/Task.h"
#include "system/TaskWithState.h"
#include "config.h"

/**
 * @brief Enum for the states of the valve.
 *
 * This enum represents the possible states of the valve: Idle and Opening.
 */
enum class ValveStates
{
    Idle,
    Opening,
};

/**
 * @brief A task for controlling a valve.
 *
 * This class represents a task for controlling a valve using a servo motor.
 * The task uses a WaterChannelController to control the water channel and a ServoMotor to control the valve.
 * The state of the task is one of the ValveStates.
 */
class ValveTask : public TaskWithState<ValveStates>
{
public:
    /**
     * @brief Constructor for a ValveTask.
     *
     * This constructor initializes a new ValveTask with the specified period, WaterChannelController, and servo pin.
     *
     * @param period The period of the task.
     * @param WaterChannelController The WaterChannelController used to control the water channel.
     * @param servoPin The pin connected to the servo motor.
     */
    ValveTask(int period, WaterChannelController *WaterChannelController, int servoPin);

    /**
     * @brief Performs the task.
     *
     * This method is called when it's time to perform the task. The actual implementation of the task is provided by subclasses.
     */
    void tick() override;

private:
    WaterChannelController *waterChannelController; ///< The WaterChannelController used to control the water channel.
    ServoMotor *motor;                              ///< The ServoMotor used to control the valve.
    unsigned int timeToMove{TIME_TO_MOVE};          ///< The time it takes for the valve to move.
};

#endif // __VALVE_TASK__