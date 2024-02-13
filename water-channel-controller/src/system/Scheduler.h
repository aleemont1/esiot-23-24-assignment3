#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "task.h"

constexpr int MAX_TASKS = 50;

/**
 * @brief A scheduler for tasks.
 *
 * This class represents a scheduler that can schedule tasks to run at certain periods.
 * The scheduler can hold up to MAX_TASKS tasks.
 */
class Scheduler
{
public:
    /**
     * @brief Constructor for a Scheduler.
     *
     * This constructor initializes a new Scheduler with the specified base period.
     *
     * @param basePeriod The base period for the scheduler.
     */
    Scheduler(int basePeriod);

    /**
     * @brief Adds a task to the scheduler.
     *
     * This method adds a task to the scheduler. If the scheduler is already full, the method returns false.
     *
     * @param task The task to add.
     * @return true if the task was added successfully, false otherwise.
     */
    virtual bool addTask(Task *task);

    /**
     * @brief Schedules the tasks in the scheduler.
     *
     * This method schedules the tasks in the scheduler to run at their specified periods.
     */
    virtual void schedule();

private:
    int basePeriod;              ///< The base period for the scheduler.
    int nTasks{0};               ///< The number of tasks currently in the scheduler.
    Task *taskList[MAX_TASKS]{}; ///< The list of tasks in the scheduler.
};

#endif // __SCHEDULER__