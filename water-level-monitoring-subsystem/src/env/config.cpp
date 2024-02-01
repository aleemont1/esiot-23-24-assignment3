/* wifi network info */

#define __CAPTIVE_PORTAL

char *captive_ssid = ""; // WiFi network SSID
char *captive_PortalDomain = "";
char *captive_query = "";

char *ssid = "";
char *password = "";
/* MQTT server address */
char *default_mqtt_server = "";   // MQTT server IP address/hostname

/* MQTT topics */
char *freq_topic = "/sensor/freq";
char *wl_topic = "/sensor/wl";

/* JSON fields */
const char *frequency_field = "FREQ";
const char *water_level_field = "WL";