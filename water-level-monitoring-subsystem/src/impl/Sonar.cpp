#include "../api/Sonar.h"

#include "Arduino.h"

#define MAX_LEVEL 30  /* cm */

Sonar::Sonar(int echoP, int trigP, long maxTime) : echoPin(echoP), trigPin(trigP), timeOut(maxTime)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  temperature = 22; /* default value */
}

void Sonar::setTemperature(float temp)
{
  temperature = temp;
}
float Sonar::getSoundSpeed()
{
  return 331.5 + 0.6 * temperature;
}

float Sonar::getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10); /* Add a delay to allow the signal to settle */

  float tUS = pulseIn(echoPin, HIGH, timeOut);
  if (tUS == 0)
  {
    return NO_OBJ_DETECTED;
  }
  else
  {
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * getSoundSpeed() * 100; /* Distance in cm */
    d = MAX_LEVEL - d;
    return d;
  }
}
