#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * Definitions go in constants.cpp
*/

/* wifi network info */
extern char *default_ssid;
extern char *default_captivePortalDomain;
extern char *default_query;

/* MQTT server address */
extern char *default_mqtt_server;

/* MQTT topics */
extern char *freq_topic;
extern char *wl_topic;

/* JSON fields */
extern const char *frequency_field;
extern const char *water_level_field;

#endif