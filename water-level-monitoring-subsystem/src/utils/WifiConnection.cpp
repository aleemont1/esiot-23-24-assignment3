#include "WifiConnection.h"
#include <WiFi.h>
#include "../env/constants.h"


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
}


void WifiConnection::setSSID(char *ssid)
{
    this->ssid = ssid;
}


char *WifiConnection::getSSID()
{
    return this->ssid;
}


void WifiConnection::setPassword(char *password)
{
    this->password = password;
}
