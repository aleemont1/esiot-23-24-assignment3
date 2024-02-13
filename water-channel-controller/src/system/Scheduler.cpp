#include "scheduler.h"
#include "TimerOne.h"
#include "logger.h"

volatile bool timerFlag;

void timerHandler(void)
{
    if (timerFlag == true)
    {
        // logger("Scheduler: Timer overrun\n");
    }
    timerFlag = true;
}

Scheduler::Scheduler(int basePeriod) : basePeriod(basePeriod)
{
    timerFlag = false;
    long period = 1000l * basePeriod;
    Timer1.initialize(period);
    Timer1.attachInterrupt(timerHandler);
}

bool Scheduler::addTask(Task *task)
{
    if (nTasks < MAX_TASKS - 1)
    {
        taskList[nTasks] = task;
        nTasks++;
        return true;
    }
    else
    {
        return false;
    }
}

void Scheduler::schedule()
{
    while (!timerFlag)
    {
    }
    for (int i = 0; i < nTasks; i++)
    {
        if (taskList[i]->updateAndCheckTime(basePeriod))
        {
            taskList[i]->tick();
        }
    }
    timerFlag = false;
}