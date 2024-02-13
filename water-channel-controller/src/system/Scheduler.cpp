#include "Scheduler.h"
#include "TimerOne.h"
#include "Logger.h"

// A flag to indicate if the timer has run.
volatile bool timerFlag = false;

void timerHandler(void)
{
    if (timerFlag)
    {
        // logger("Scheduler: Timer overrun\n");
        return;
    }
    timerFlag = true;
}

Scheduler::Scheduler(int basePeriod) : basePeriod(basePeriod)
{
    // The conversion is preventing potential overflow if basePeriod is a large int.
    const long period = 1000l * static_cast<long>(basePeriod);
    Timer1.initialize(period);
    Timer1.attachInterrupt(timerHandler);
}

bool Scheduler::addTask(Task *task)
{
    if (task == nullptr || nTasks >= MAX_TASKS)
    {
        return false;
    }

    taskList[nTasks++] = task;
    return true;
}

void Scheduler::schedule()
{
    while (!timerFlag)
    {
        // Do nothing, just wait for the timerFlag to be set
    }

    for (Task *task : taskList)
    {
        if (task && task->updateAndCheckTime(basePeriod))
        {
            task->tick();
        }
    }

    timerFlag = false;
}