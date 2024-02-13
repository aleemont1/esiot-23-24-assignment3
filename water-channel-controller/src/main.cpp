#include "serial_communication/Client-Arduino/ValveController.h"
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
  scheduler->addTask(new LcdTask(150, &waterChannelController, 0x27, 16, 2));
  scheduler->addTask(new InputTask(100, &waterChannelController, BUTTON_PIN, POT_PIN));
  scheduler->addTask(new ValveTask(105, &waterChannelController, SERVO_PIN));
  scheduler->addTask(new SerialCommunicationTask(100, JsonProcessor(), &waterChannelController));
}

void loop()
{
  scheduler->schedule();
}
