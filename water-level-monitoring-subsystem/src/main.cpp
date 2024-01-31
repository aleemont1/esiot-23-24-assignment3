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
char *ssid = "Mont";
char *password = "a26062002";
WifiConnection wifiConn = WifiConnection(ssid, password);
#endif

WiFiClient espClient;
MQTTpublisher publisher = MQTTpublisher(default_mqtt_server, "espClient", "freq");
MQTTsubscriber subscriber = MQTTsubscriber(default_mqtt_server, "espClient");

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
  subscriber.subscribe("freq");
  subscriber.subscribe("sensor");
  // Serial.println(publisher.connected());
  // subscriber = MQTTsubscriber(default_mqtt_server, freq_topic);
}

void loop()
{

  Serial.println("Frequency: " + String(frequency));
  Serial.println("Sonar: " + String(sonar.getDistance()));
  publisher.loop();
  subscriber.loop();
  publisher.publish(String(frequency).c_str());
  publisher.publish("sensor", String(sonar.getDistance()).c_str());
  delay(1000);
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