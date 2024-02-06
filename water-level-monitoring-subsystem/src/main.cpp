#include "api/MQTTpublisher.h"
#include "api/MQTTsubscriber.h"
#include "api/Sonar.h"
#include "env/config.h"
#include <WiFiClient.h>
#include <WiFi.h>

/*#define __CAPTIVE_PORTAL*/

/*#ifdef __CAPTIVE_PORTAL*/

//#include "utils/CaptivePortalConnection.h"
//CaptivePortalConnection wifiConn = CaptivePortalConnection();
//#else

#include "utils/WifiConnection.h"
/**
 * NOTE: Create ssid and password in env/config.h
 */
WifiConnection wifiConn = WifiConnection(ssid, password);


Sonar sonar = Sonar(ECHO_PIN, TRIG_PIN, SONAR_TIMER);

WiFiClient espClient;
/**NOTE: default_mqtt_server is defined in constants.cpp**/
MQTTpublisher publisher = MQTTpublisher(default_mqtt_server, "espPublisher");
MQTTsubscriber subscriber = MQTTsubscriber(default_mqtt_server, "espSubscriber");

unsigned long lastMsgTime = 0;

/* Publish/Read frequency (in ms, can be changed) */
unsigned int frequency = 2000; // 2 seconds default

// Define your tasks
void TaskPublisher(void *pvParameters);
void TaskSubscriber(void *pvParameters);
void TaskCheckConnection(void *pvParameters);

void turnGreenLedOn();
void turnGreenLedOff();
void turnRedLedOn();

void setup()
{
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Serial.begin(115200);
  turnRedLedOn();
  wifiConn.setup_wifi();

  publisher.connect();
  subscriber.connect();
  subscriber.subscribeJSON(freq_topic);

  // Create the tasks
  xTaskCreate(
      TaskPublisher,
      "Publisher", // Task name
      2000,        // Stack size
      NULL,        // Task input parameter
      1,           // Priority
      NULL);       // Task handle

  xTaskCreate(
      TaskSubscriber,
      "Subscriber", // Task name
      2000,         // Stack size
      NULL,         // Task input parameter
      1,            // Priority
      NULL);        // Task handle

  xTaskCreate(
      TaskCheckConnection,
      "CheckConnection", // Task name
      2000,              // Stack size
      NULL,              // Task input parameter
      1,                 // Priority
      NULL);             // Task handle
}

void loop()
{
}

void TaskPublisher(void *pvParameters)
{
  for (;;)
  {
    publisher.loop();
    unsigned long now = millis();
    if (now - lastMsgTime > frequency)
    {
      turnGreenLedOn();
      // Serial.println("Publishing with frequency: " + String(frequency) + "ms");
      char wl_char[SONAR_MSG_SIZE];
      snprintf(wl_char, SONAR_MSG_SIZE, "%.2f", sonar.getDistance()); // test value
      // Serial.println("Publishing water level: " + String(wl_char));
      publisher.publishJSON(wl_topic, water_level_field, wl_char);
      lastMsgTime = now;
    }
    vTaskDelay(1); // Yield to other tasks
    turnGreenLedOff();
  }
}

void TaskSubscriber(void *pvParameters)
{
  for (;;)
  {
    subscriber.loop();
    turnGreenLedOn();
    int payload = subscriber.getSavedPayloadInt();
    if (payload > 0)
    {
      if (payload != frequency)
      {
        frequency = payload;
        Serial.println("New frequency: " + String(frequency) + "ms");
      }
    }
    else
    {
      Serial.println("Invalid Payload (retrying)");
    }
    vTaskDelay(1); // Yield to other tasks
    turnGreenLedOff();
  }
}

void TaskCheckConnection(void *pvParameters)
{
  for (;;)
  {
    while (wifiConn.status() != WL_CONNECTED)
    {
      turnRedLedOn();
      Serial.println("WiFi disconnected");
      wifiConn.setup_wifi();
    }

    while (publisher.connected() == false)
    {
      turnRedLedOn();
      Serial.println("MQTT publisher disconnected... trying to reconnect in 3s");
      publisher.connect();
      vTaskDelay(3000);
    }

    while (subscriber.connected() == false)
    {
      turnRedLedOn();
      Serial.println("MQTT subscriber disconnected... trying to reconnect in 3s");
      subscriber.connect();
      vTaskDelay(3000);
    }
    vTaskDelay(2000); // Delay between connection checks
  }
}

void turnGreenLedOn()
{
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
}

void turnGreenLedOff()
{
  digitalWrite(GREEN_LED, LOW);
}

void turnRedLedOn()
{
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
}