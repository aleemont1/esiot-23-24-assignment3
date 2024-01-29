#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>

#define MSG_BUFFER_SIZE  50

/* wifi network info */

const char *ssid = "ergo-latorre";
const String captivePortalDomain = "latorre.er-go.it/login";
const String query = "username=1200019&password=Ybj3qDfH&dst=&popup=true";
const String msg = "msg=Hello%20altair!%20from%20esp32&id=";


/* MQTT server address */
const char* mqtt_server = "10.250.23.142";

/* MQTT topic */
const char* topic = "test";

// Frequenza di invio dei messaggi al server
int frequency = 5000;
/* MQTT client management */

WiFiClient espClient;
PubSubClient client(espClient);


unsigned long lastMsgTime = 0;
char mess[MSG_BUFFER_SIZE];
int value = 0;


void setup_wifi() {
  Serial.begin(115200);
  delay(10);

  Serial.println(String("Connecting to ") + ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  HTTPClient login;
  login.begin(captivePortalDomain);
  login.addHeader("Content-Type", "application/x-www-form-urlencoded");
  Serial.println("Sending POST request for login");
  int httpCode = login.POST(query);
  String payload = login.getString();
}

/* MQTT subscribing callback */

void callback(char* topic, byte* payload, unsigned int length) {
  char *buff = (char *)malloc(length+1);
  for(int i=0; i<length; i++) {
    buff[i] = (char)payload[i];
  }
  Serial.println(String("Message arrived on [") + topic + "] len: " + length + " " + buff);
  // setFrequency(toInt(payload));
}

void reconnect() {
  
  // Loop until we're reconnected
  
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > frequency) {
    lastMsgTime = now;
    value++;

    /* creating a msg in the buffer */
    snprintf (mess, MSG_BUFFER_SIZE, "Sonar.getValue() #%ld", value);     // Sonar.getValue() deve ritornare il livello dell'acqua (Il campo deve chiamarsi WL)
                                                                          // e la frequenza (il campo deve chiamarsi FREQ) in formato JSON.
    Serial.println(String("Publishing message: ") + mess);
    
    /* publishing the msg */
    client.publish(topic, mess);  
  }
}

