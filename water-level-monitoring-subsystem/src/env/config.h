#ifndef CONFIG_H
#define CONFIG_H

/**
 * Definitions go in constants.cpp
*/

/* sonar sensor info */
#define ECHO_PIN 5
#define TRIG_PIN 18
#define SONAR_TIMER 10000

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