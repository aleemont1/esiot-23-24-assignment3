// WifiConnection.cpp
#include "WifiConnection.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "../constants.h"

void WifiConnection::setup_wifi()
{

    const String captivePortalDomain = "latorre.er-go.it/login";
    const String query = "username=1200019&password=Ybj3qDfH&dst=&popup=true";
    
    Serial.begin(115200);
    delay(10);

    Serial.println(String("Connecting to ") + ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid);

    while (WiFi.status() != WL_CONNECTED)
    {
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