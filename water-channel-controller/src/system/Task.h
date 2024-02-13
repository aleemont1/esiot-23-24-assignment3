#ifndef __TASK__
#define __TASK__

/**
 * @brief Abstract base class for a task.
 *
 * This class represents a task that can be scheduled to run at a certain period.
 * The actual task is implemented by subclasses in the `tick` method.
 */
class Task
{

public:
    /**
     * @brief Constructor for a Task.
     *
     * This constructor initializes a new Task with the specified period.
     *
     * @param period The period of the task.
     */
    Task(int period) : myPeriod(period) {}

    /**
     * @brief Virtual method for the task to be performed.
     *
     * This method is implemented by subclasses to perform the actual task.
     */
    virtual void tick() = 0;

    /**
     * @brief Get the period of the task.
     *
     * @return The period of the task.
     */
    int getPeriod() const { return myPeriod; }

    /**
     * @brief Set the period of the task.
     *
     * @param period The new period of the task.
     */
    void setPeriod(int period) { myPeriod = period; }

    /**
     * @brief Get the elapsed time since the last time the task was performed.
     *
     * @return The elapsed time.
     */
    int getTimeElapsed() const { return timeElapsed; }

    /**
     * @brief Set the elapsed time since the last time the task was performed.
     *
     * @param time The new elapsed time.
     */
    void setTimeElapsed(int time) { timeElapsed = time; }

    /**
     * @brief Updates the elapsed time and checks if it's time to perform the task.
     *
     * This method increments the elapsed time by the base period and checks if it's time to perform the task.
     * If the elapsed time is greater than or equal to the task's period, the elapsed time is reset to 0 and the method returns true.
     * Otherwise, the method returns false.
     *
     * @param basePeriod The base period to increment the elapsed time by.
     * @return true if it's time to perform the task, false otherwise.
     */
    bool updateAndCheckTime(int basePeriod)
    {
        timeElapsed += basePeriod;
        if (timeElapsed < myPeriod)
        {
            return false;
        }

        timeElapsed = 0;
        return true;
    }

private:
    int myPeriod;       ///< The period of the task.
    int timeElapsed{0}; ///< The elapsed time since the last time the task was performed.
};

#endif // __TASK__