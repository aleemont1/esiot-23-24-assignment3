#ifndef __VALVE_TASK__
#define __VALVE_TASK__

#include "WaterChannelController.h"
#include "../components/api/ServoMotor.h"
#include "system/Task.h"
#include "system/TaskWithState.h"
#include "Config.h"

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

    /**
     * @brief Initializes the servo motor.
     *
     * This method initializes the servo motor by turning it on and setting its position to the minimum angle.
     */
    void initializeMotor();

    /**
     * @brief Handles the Idle state.
     *
     * This method handles the Idle state by updating the position of the servo motor based on the position of the water channel.
     */
    void handleIdleState();

    /**
     * @brief Handles the Opening state.
     *
     * This method handles the Opening state by checking if the valve has been open for the specified time and then setting the state to Idle.
     */
    void handleOpeningState();

    /**
     * @brief Checks if the time to move has elapsed.
     *
     * This method checks if the time to move has elapsed by comparing the elapsed time in the current state to the time to move.
     *
     * @return bool True if the time to move has elapsed, false otherwise.
     */
    bool isTimeToMoveElapsed();

    /**
     * @brief Transitions to the Idle state.
     *
     * This method transitions to the Idle state by setting the state to Idle.
     */
    void transitionToIdleState();

    /**
     * @brief Checks if the position has changed.
     *
     * This method checks if the position of the water channel has changed.
     *
     * @return bool True if the position has changed, false otherwise.
     */
    bool isPositionChanged();

    /**
     * @brief Updates the position of the servo motor.
     *
     * This method updates the position of the servo motor based on the position of the water channel.
     */

    void updateMotorPosition();

    /**
     * @brief Resets the position change flag.
     *
     * This method resets the position change flag of the water channel controller.
     */
    void resetPositionChangeFlag();

    /**
     * @brief Turns the servo motor on.
     *
     * This method turns the servo motor on.
     */
    void turnMotorOn();

    /**
     * @brief Sets the position of the servo motor to the minimum angle.
     *
     * This method sets the position of the servo motor to the minimum angle.
     */
    void setMotorToMinAngle();

private:
    WaterChannelController *waterChannelController; ///< The WaterChannelController used to control the water channel.
    ServoMotor *motor;                              ///< The ServoMotor used to control the valve.
    unsigned int timeToMove{TIME_TO_MOVE};          ///< The time it takes for the valve to move.
    const int MIN_POSITION_PERCENT = 0;             ///< The minimum position percentage of the water channel.
    const int MAX_POSITION_PERCENT = 100;           ///< The maximum position percentage of the water channel.
    const int MIN_SERVO_ANGLE = 0;                  ///< The minimum angle of the servo motor.
    const int MAX_SERVO_ANGLE = 180;                ///< The maximum angle of the servo motor.
};

#endif // __VALVE_TASK__