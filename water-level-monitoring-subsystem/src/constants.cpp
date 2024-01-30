#include <Arduino.h> // Include the necessary header file for the 'String' type

/* wifi network info */
char *default_ssid = ""; // WiFi network SSID
char *default_captivePortalDomain = "";
char *default_query = "";

/* MQTT server address */
const char *mqtt_server = "altair";   // MQTT server IP address/hostname

/* MQTT topicS */
const char *freq_topic = "sensor/freq";
const char *wl_topic = "sensor/wl";