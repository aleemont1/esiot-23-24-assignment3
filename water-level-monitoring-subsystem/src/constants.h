#ifndef CONSTANTS_H
#define CONSTANTS_H

/* wifi network info */
#include <Arduino.h> // Include the necessary header file for the 'String' type

extern const char *ssid;
extern const String captivePortalDomain;
extern const String query;
extern const String msg;

/* MQTT server address */
extern const char *mqtt_server;

/* MQTT topicS */
extern const char *freq_topic;
extern const char *wl_topic;

#endif