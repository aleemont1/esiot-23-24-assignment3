#include <Arduino.h> // Include the necessary header file for the 'String' type

/* wifi network info */
char *default_ssid = "ergo-latorre"; // WiFi network SSID
char *default_captivePortalDomain = "latorre.er-go.it/login";
char *default_query = "username=1200019&password=Ybj3qDfH&dst=&popup=true";

/* MQTT server address */
char *default_mqtt_server = "10.250.23.142";   // MQTT server IP address/hostname

/* MQTT topics */
char *freq_topic = "sensor/freq";
char *wl_topic = "sensor/wl";