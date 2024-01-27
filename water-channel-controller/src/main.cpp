#include "serial_communication/Client-Arduino/SerialCommunication.h"
#include "Arduino.h"

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  SerialCommunicationChannel commChannel;
  String content = commChannel.getReceivedContent();
}