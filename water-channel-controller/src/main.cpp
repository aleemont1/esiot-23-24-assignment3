#include "system/Scheduler.h"
#include "task/InputTask.h"
#include "task/ValveTask.h"
#include "Config.h"
#include "task/LcdTask.h"
#include "system/SerialComm.h"
#include "Arduino.h"

Scheduler *scheduler;
WaterChannelController waterChannelController;
SerialComm serialComm;

void setup()
{
  Serial.begin(9600);
  scheduler = new Scheduler(BASE_PERIOD);

  // Initialize the task and add them to the scheduler
  scheduler->addTask(new LcdTask(200, &waterChannelController, 0x27, 16, 2));
  scheduler->addTask(new InputTask(100, &waterChannelController, BUTTON_PIN, POT_PIN));
  scheduler->addTask(new ValveTask(100, &waterChannelController, SERVO_PIN));
}

void loop()
{
  serialComm.serialCommunication();
  scheduler->schedule();
}
