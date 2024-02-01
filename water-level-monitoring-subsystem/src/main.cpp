#include "api/MQTTpublisher.h"
#include "api/MQTTsubscriber.h"
#include "api/Sonar.h"
#include "env/config.h"

#ifdef __CAPTIVE_PORTAL
#include "utils/CaptivePortalConnection.h"
#else
#include "utils/WifiConnection.h"
#endif

#include <WiFiClient.h>

#define FREQ_MSG_SIZE 16
#define SONAR_MSG_SIZE 16

#ifdef __CAPTIVE_PORTAL
CaptivePortalConnection wifiConn = CaptivePortalConnection();
#else
/**
 * NOTE: Create ssid and password in env/config.h
 */

WifiConnection wifiConn = WifiConnection(ssid, password);
#endif

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

void setup()
{
  Serial.begin(115200);
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
      2,           // Priority
      NULL);       // Task handle

  xTaskCreate(
      TaskSubscriber,
      "Subscriber", // Task name
      2000,         // Stack size
      NULL,         // Task input parameter
      1,            // Priority
      NULL);        // Task handle
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
      // Serial.println("Publishing with frequency: " + String(frequency) + "ms");
      char wl_char[SONAR_MSG_SIZE];
      snprintf(wl_char, SONAR_MSG_SIZE, "%.2f", sonar.getDistance() * 100); // test value
      // Serial.println("Publishing water level: " + String(wl_char));
      publisher.publishJSON(wl_topic, water_level_field, wl_char);
      lastMsgTime = now;
    }
    vTaskDelay(1); // Yield to other tasks
  }
}

void TaskSubscriber(void *pvParameters)
{
  for (;;)
  {
    subscriber.loop();
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
  }
}