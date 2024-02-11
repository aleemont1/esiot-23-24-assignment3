#include "serial_communication/Client-Arduino/SerialCommunication.h"
#include "WaterChannelController/WaterChannelController.h"
#include "serial_communication/Client-Arduino/ValveController.h"
#include "Arduino.h"

void setup()
{
  Serial.begin(9600);
  delay(10);
}

void loop()
{
  JsonProcessor jsonProcessor;
  SerialCommunicationChannel commChannel(jsonProcessor);
  commChannel.initializeSerialCommunication();
  WaterChannelController waterChannelController(9, 4, A0, 0x27, 16, 2);
  waterChannelController.reading();
}
