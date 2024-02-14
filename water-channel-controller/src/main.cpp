#include "system/Scheduler.h"
#include "task/InputTask.h"
#include "task/ValveTask.h"
#include "task/SerialCommunicationTask.h"
#include "Config.h"
#include "task/LcdTask.h"
#include "Arduino.h"

Scheduler *scheduler;
WaterChannelController waterChannelController;

void setup()
{
  scheduler = new Scheduler(BASE_PERIOD);

  // Initialize the task and add them to the scheduler
  scheduler->addTask(new LcdTask(200, &waterChannelController, 0x27, 16, 2));
  scheduler->addTask(new InputTask(100, &waterChannelController, BUTTON_PIN, POT_PIN));
  scheduler->addTask(new ValveTask(100, &waterChannelController, SERVO_PIN));
  scheduler->addTask(new SerialCommunicationTask(200, JsonProcessor(), &waterChannelController));
}

void loop()
{
  scheduler->schedule();
}
