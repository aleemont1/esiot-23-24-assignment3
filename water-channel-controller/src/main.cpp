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
  Serial.begin(9600);
  scheduler = new Scheduler(BASE_PERIOD);

  // Initialize the task and add them to the scheduler
  scheduler->addTask(new LcdTask(200, &waterChannelController, 0x27, 16, 2));
  scheduler->addTask(new InputTask(100, &waterChannelController, BUTTON_PIN, POT_PIN));
  scheduler->addTask(new ValveTask(100, &waterChannelController, SERVO_PIN));
}

void loop()
{
  String receivedContent;
  String valveValue;
  if (Serial.available())
  {
    receivedContent = Serial.readStringUntil('\n');
    JsonDocument doc;
    deserializeJson(doc, receivedContent);
    String status = doc["status"];

    if (status == "ALARM_TOO_LOW")
    {
      Serial.println("{\"status\": \"ALARM_TOO_LOW\",\"valveValue\": 0}");
    }
    else if (status == "NORMAL")
    {
      Serial.println("{\"status\":\"NORMAL\",\"valveValue\": 25}");
    }
    else if (status == "PRE_ALARM_TOO_HIGH")
    {
      Serial.println("{\"status\":\"PRE_ALARM_TOO_HIGH\",\"valveValue\": 40}");
    }
    else if (status == "ALARM_TOO_HIGH")
    {
      Serial.println("{\"status\":\"ALARM_TOO_HIGH\",\"valveValue\": 50}");
    }
    else if (status == "ALARM_TOO_HIGH_CRITIC")
    {
      Serial.println("{\"status\":\"ALARM_TOO_HIGH_CRITIC\",\"valveValue\": 100}");
        }
    else
    {
      valveValue = "unknown state";
    }
  }
  scheduler->schedule();
}
