#include "serial_communication/Client-Arduino/SerialCommunication.h"
#include "Arduino.h"

void setup()
{
  Serial.begin(9600);

  // SerialCommunicationChannel commChannel;

  // // Test sending a message
  // commChannel.sendMessage("Hello from Arduino!");

  // // Test checking message availability
  // bool isAvailable = commChannel.checkMessageAvailability();
  // Serial.println(isAvailable ? "Message is available" : "No message available");

  // // Test getting received content
  // String content = commChannel.getReceivedContent();
  // Serial.println("Received content: " + content);
}

void loop()
{
  Serial.println("Hello from Arduino!");
}