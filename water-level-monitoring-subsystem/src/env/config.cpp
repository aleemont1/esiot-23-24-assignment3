#include "config.h"

/* wifi network info */
#ifdef __CAPTIVE_PORTAL

const char *captive_ssid = "ergo-latorre";
const char *captive_PortalDomain = "latorre.er-go.it/login";
const char *captive_query = "username=1200019&password=Ybj3qDfH&dst=&popup=true";

#else

const char *ssid = "";
const char *password = "";

#endif
/* MQTT server address */
const char *default_mqtt_server = "10.250.23.170";

/* MQTT topics */
const char *freq_topic = "/sensor/freq";
const char *wl_topic = "/sensor/wl";

/* JSON fields */
const char *frequency_field = "freq";
const char *water_level_field = "WL";