#ifndef __TASK_WITH_STATE__
#define __TASK_WITH_STATE__

#include "Arduino.h"
#include "system/task.h"

/**
 * @brief A task with a state.
 *
 * This class represents a task that has a state. The state can be of any type.
 * The class provides methods to set and get the state, and to get the elapsed time since the state was last set.
 *
 * @param T The type of the state.
 */
template <typename T>
class TaskWithState : public Task
{
public:
    /**
     * @brief Constructor for a TaskWithState.
     *
     * This constructor initializes a new TaskWithState with the specified period and initializes the state.
     *
     * @param period The period of the task.
     * @param initialState The initial state of the task.
     */
    TaskWithState(int period, T initialState = T())
        : Task(period), state(initialState)
    {
    }

protected:
    /**
     * @brief Sets the state of the task.
     *
     * This method sets the state of the task and updates the state timestamp to the current time.
     *
     * @param s The new state.
     */
    void setState(T s)
    {
        state = s;
        stateTimestamp = millis();
    }

    /**
     * @brief Gets the state of the task.
     *
     * This method returns the current state of the task.
     *
     * @return The current state of the task.
     */
    T getState()
    {
        return this->state;
    }

    /**
     * @brief Gets the elapsed time in the current state.
     *
     * This method returns the elapsed time since the state was last set.
     *
     * @return The elapsed time in the current state.
     */
    unsigned long elapsedTimeInState()
    {
        return millis() - stateTimestamp;
    }

private:
    T state;                         ///< The current state of the task.
    unsigned long stateTimestamp{0}; ///< The timestamp when the state was last set.
};

#endif // __TASK_WITH_STATE__