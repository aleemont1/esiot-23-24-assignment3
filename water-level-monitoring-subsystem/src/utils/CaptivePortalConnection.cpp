// CaptivePortalConnection
#include "CaptivePortalConnection.h"
#include "../env/constants.h"
#include <WiFi.h>
#include <HTTPClient.h>

CaptivePortalConnection::CaptivePortalConnection() {
    this->ssid = captive_ssid;
    this->captivePortalDomain = captive_PortalDomain;
    this->query = captive_query;
}

CaptivePortalConnection::CaptivePortalConnection(char *ssid, char *captivePortalDomain, char *query)
{
    this->ssid = ssid;
    this->captivePortalDomain = captivePortalDomain;
    this->query = query;
}

void CaptivePortalConnection::setup_wifi()
{
    Serial.begin(115200);
    delay(10);

    Serial.println(String("Connecting to ") + this->getSSID());

    WiFi.mode(WIFI_STA);
    WiFi.begin(this->getSSID());

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
    login.begin(this->getCaptive());
    login.addHeader("Content-Type", "application/x-www-form-urlencoded");
    Serial.println("Sending POST request for login");
    login.POST(this->getQuery());
    String payload = login.getString();
}

void CaptivePortalConnection::setSSID(char *ssid)
{
    this->ssid = ssid;
}

char *CaptivePortalConnection::getSSID()
{
    return this->ssid;
}

void CaptivePortalConnection::setCaptive(char *captivePortalDomain)
{
    this->captivePortalDomain = captivePortalDomain;
}

char *CaptivePortalConnection::getCaptive()
{
    return this->captivePortalDomain;
}

void CaptivePortalConnection::setQuery(char *query)
{
    this->query = query;
}

char *CaptivePortalConnection::getQuery()
{
    return this->query;
}