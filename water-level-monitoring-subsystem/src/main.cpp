// #define __CAPTIVE_PORTAL
#ifdef __CAPTIVE_PORTAL
#include "utils/CaptivePortalConnection.h"
#else
#include "utils/WifiConnection.h"
#endif

#include "api/MQTTpublisher.h"
#include "api/MQTTsubscriber.h"
#include <WiFiClient.h>
#include "api/Sonar.h"
#include "env/constants.h"

#define FREQ_MSG_SIZE 16
#define SONAR_MSG_SIZE 16

#ifdef __CAPTIVE_PORTAL
CaptivePortalConnection wifiConn = CaptivePortalConnection();
#else
/**
 * Create ssid and password in env/constants.h
 */
char *ssid = "";
char *password = "";
WifiConnection wifiConn = WifiConnection(ssid, password);
#endif

WiFiClient espClient;
MQTTpublisher publisher = MQTTpublisher(default_mqtt_server, "espPublisher");
MQTTsubscriber subscriber = MQTTsubscriber(default_mqtt_server, "espSubscriber");

unsigned long lastMsgTime = 0;

char freq_msg[FREQ_MSG_SIZE];
char sonar_msg[SONAR_MSG_SIZE];

/* Frequenza di invio dei messaggi al server */
unsigned int frequency = 2000;    // 2 seconds default
Sonar sonar = Sonar(12, 13, 500); // random values, to be changed

// void setFrequency(int freq);
// unsigned int getFrequency();

void setup()
{

  Serial.begin(115200);
  wifiConn.setup_wifi();
  randomSeed(micros());

  publisher.connect();
  subscriber.connect();

  subscriber.subscribeJSON(freq_topic);
}

void loop()
{
  publisher.loop();
  subscriber.loop();
  unsigned long now = millis();

  if (now - lastMsgTime > frequency)
  {
    char wl_char[SONAR_MSG_SIZE];
    // snprintf(wl_char, SONAR_MSG_SIZE, "%d", sonar.getDistance());
    snprintf(wl_char, SONAR_MSG_SIZE, "%d", 100);
    Serial.println("Publishing water level: " + String(wl_char));
    publisher.publishJSON(wl_topic, water_level_field, wl_char);
    int receivedFrequency = 0;
    int payload = subscriber.getSavedPayloadInt();
    if (payload > 0)
    {
      Serial.println("Received payload: " + String(payload));
      frequency = payload;
      Serial.println("New frequency: " + String(frequency));
    }
    else
    {
      Serial.println("Payload is NULL");
    }
    lastMsgTime = millis();
  }
}

// void setFrequency(int freq)
// {
//   // frequency = atoi(subscriber.getPayload());
// }

// unsigned int getFrequency()
// {
//   // return atoi(subscriber.getPayload());
//   return -1;
// }