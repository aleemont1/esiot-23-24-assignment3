#ifndef CONFIG_H
#define CONFIG_H

/* LEDs PINs */
#define GREEN_LED 19
#define RED_LED 21

/* sonar sensor info */
#define ECHO_PIN 5
#define TRIG_PIN 18
#define SONAR_TIMER 10000

/* mqtt buffers dimensions*/
#define FREQ_MSG_SIZE 16
#define SONAR_MSG_SIZE 16
//#define __CAPTIVE_PORTAL /* Comment this line to use a regular WiFi network */

extern const char *captive_ssid;
extern const char *captive_PortalDomain;
extern const char *captive_query;


extern const char *ssid;
extern const char *password;

/* MQTT server address */
extern const char *default_mqtt_server; /* MQTT server IP address/hostname */

/* MQTT topics */
extern const char *freq_topic;
extern const char *wl_topic;

/* JSON fields */
extern const char *frequency_field;
extern const char *water_level_field;

#endif /* CONFIG_H */