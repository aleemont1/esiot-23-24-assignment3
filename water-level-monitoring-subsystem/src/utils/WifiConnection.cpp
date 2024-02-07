#include <WiFi.h>
#include "WifiConnection.h"
#include "../env/config.h"


WifiConnection::WifiConnection()
{
    this->ssid = ssid;
    this->password = nullptr;
}


WifiConnection::WifiConnection(char *ssid)
{
    this->ssid = ssid;
    this->password = nullptr;
}


WifiConnection::WifiConnection(char *ssid, char *password)
{
    this->ssid = ssid;
    this->password = password;
}


void WifiConnection::setup_wifi()
{
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    Serial.println("Connecting to WiFi network: " + String(this->ssid));
    if (this->password == nullptr)
    {
        WiFi.begin(this->ssid);
    }
    else
    {
        WiFi.begin(this->ssid, this->password);
    }
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    digitalWrite(RED_LED, LOW);
}


void WifiConnection::setSSID(const char *ssid)
{
    this->ssid = ssid;
}


const char *WifiConnection::getSSID()
{
    return this->ssid;
}


void WifiConnection::setPassword(char *password)
{
    this->password = password;
}

int WifiConnection::status()
{
    return WiFi.status();
}