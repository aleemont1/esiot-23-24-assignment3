#include "config.h"

/* wifi network info */

const char *captive_ssid = "";
const char *captive_PortalDomain = "";
const char *captive_query = "";

const char *ssid = "";
const char *password = "";

/* MQTT server address */
const char *default_mqtt_server = "";

/* MQTT topics */
const char *freq_topic = "/sensor/freq";
const char *wl_topic = "/sensor/wl";

/* JSON fields */
const char *frequency_field = "freq";
const char *water_level_field = "WL";