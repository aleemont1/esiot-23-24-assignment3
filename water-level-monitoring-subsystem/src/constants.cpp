#include <Arduino.h> // Include the necessary header file for the 'String' type

/* wifi network info */

const char *ssid = "ergo-latorre";


/* MQTT server address */
const char *mqtt_server = "10.250.23.142";

/* MQTT topicS */
const char *freq_topic = "sensor/freq";
const char *wl_topic = "sensor/wl";