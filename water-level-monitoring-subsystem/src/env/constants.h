#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * Definitions go in constants.cpp
*/

/* wifi network info */
extern char *captive_ssid;
extern char *captive_PortalDomain;
extern char *captive_query;

extern char *ssid;
extern char *password;
/* MQTT server address */
extern char *default_mqtt_server;

/* MQTT topics */
extern char *freq_topic;
extern char *wl_topic;

/* JSON fields */
extern const char *frequency_field;
extern const char *water_level_field;

#endif