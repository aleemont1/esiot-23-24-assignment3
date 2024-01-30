#include <Arduino.h> // Include the necessary header file for the 'String' type

/* wifi network info */
char *default_ssid = ""; // WiFi network SSID
char *default_captivePortalDomain = "";
char *default_query = "";

/* MQTT server address */
char *default_mqtt_server = "";   // MQTT server IP address/hostname

/* MQTT topics */
char *freq_topic = "sensor/freq";
char *wl_topic = "sensor/wl";