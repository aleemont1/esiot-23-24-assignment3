#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include "api/Sonar.h"
#include "utils/CaptivePortalConnection.h"
#include "constants.h"

#define FREQ_MSG_SIZE 16
#define SONAR_MSG_SIZE 16

/* MQTT client management */

WiFiClient espClient;
PubSubClient client(espClient);
CaptivePortalConnection wifiConn = CaptivePortalConnection();

unsigned long lastMsgTime = 0;
char freq_msg[FREQ_MSG_SIZE];
char sonar_msg[SONAR_MSG_SIZE];

/* Frequenza di invio dei messaggi al server */
unsigned int frequency = 2000; // 2 seconds default

Sonar sonar = Sonar(12, 13, 500); // random values, to be changed

/* MQTT subscribing callback */

void callback(char *topic, byte *payload, unsigned int length)
{
  char *buff = (char *)malloc(length + 1);
  for (int i = 0; i < length; i++)
  {
    buff[i] = (char)payload[i];
  }
  Serial.println(String("Message arrived on [") + topic + "] len: " + length + " " + buff);
  // setFrequency(toInt(payload));
  free(buff);
}

void setFrequency(int freq)
{
  frequency = freq;
}

unsigned int getFrequency()
{
  return frequency;
}

unsigned long getSonarValue()
{
  return sonar.getDistance();
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    // Create a random client ID
    String clientId = String("water-level-monitor-") + String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe(freq_topic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds...");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  wifiConn.setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > frequency)
  {
    lastMsgTime = now;

    /* creating a msg in the buffer 
     *
     * NOTE TO SELF: Use JSON serializer
     */
    snprintf(freq_msg, FREQ_MSG_SIZE, "{\"FREQ\":\"%d\"}", getFrequency());    // getFrequency() deve ritornare il livello dell'acqua (Il campo deve chiamarsi FREQ)                                                          
    snprintf(sonar_msg, SONAR_MSG_SIZE, "{\"WL\":\"%d\"}", getSonarValue()); // Sonar.getValue() deve ritornare il livello dell'acqua (Il campo deve chiamarsi WL)

    Serial.println(String("Publishing message: ") + freq_msg + " on topic: " + freq_topic);
    Serial.println(String("Publishing message: ") + sonar_msg + " on topic: " + wl_topic);

    /* publishing the msg */
    client.publish(freq_topic, freq_msg);
    client.publish(wl_topic, sonar_msg);
  }
}
