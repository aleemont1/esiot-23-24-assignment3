/* wifi network info */

#define __CAPTIVE_PORTAL

char *captive_ssid = ""; // WiFi network SSID
char *captive_PortalDomain = "";
char *captive_query = "";

char *ssid = "Mont";
char *password = "a26062002";
/* MQTT server address */
char *default_mqtt_server = "192.168.112.147";   // MQTT server IP address/hostname

/* MQTT topics */
char *freq_topic = "/sensor/freq";
char *wl_topic = "/sensor/wl";

/* JSON fields */
const char *frequency_field = "FREQ";
const char *water_level_field = "WL";