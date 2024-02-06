/* wifi network info */

char *captive_ssid = "ergo-latorre"; // WiFi network SSID
char *captive_PortalDomain = "latorre.er-go.it/login";
char *captive_query = "username=1200019&password=Ybj3qDfH&dst=&popup=true";
char *ssid = "";
char *password = "";
/* MQTT server address */
char *default_mqtt_server = "10.250.23.179";   // MQTT server IP address/hostname

/* MQTT topics */
char *freq_topic = "/sensor/freq";
char *wl_topic = "/sensor/wl";

/* JSON fields */
const char *frequency_field = "FREQ";
const char *water_level_field = "WL";