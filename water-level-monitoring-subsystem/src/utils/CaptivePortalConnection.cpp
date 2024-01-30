// CaptivePortalConnection
#include "CaptivePortalConnection.h"
#include "../constants.h"
#include <WiFi.h>
#include <HTTPClient.h>

/**
 * 
 * @brief Construct a new CaptivePortalConnection object
 * @param ssid WiFi network SSID
 * @param captivePortalDomain URL or IP of the radius server
 * @param query Usually a POST request
 * 
*/
CaptivePortalConnection::CaptivePortalConnection(char *ssid, char *captivePortalDomain, char *query)
{
    this->ssid = ssid;
    this->captivePortalDomain = captivePortalDomain;
    this->query = query;
}

/**
 * @brief Construct a new CaptivePortalConnection object
 * 
 * Default values for ssid, captivePortalDomain and query are used 
 * (see \ref ../constants.h)
 * 
 */
CaptivePortalConnection::CaptivePortalConnection() {
    this->ssid = default_ssid;
    this->captivePortalDomain = default_captivePortalDomain;
    this->query = default_query;
}

/**
 * @brief Initialize WiFi connection
 * 
*/
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
    int httpCode = login.POST(this->getQuery());
    String payload = login.getString();
}

/**
 * @brief Set the captive portal domain
 * 
 * @param captivePortalDomain URL or IP of the radius server
 * 
*/
void CaptivePortalConnection::setCaptive(char *captivePortalDomain)
{
    this->captivePortalDomain = captivePortalDomain;
}

/**
 * @brief Set the query for the radius server
 * 
 * @param query Usually a POST request
*/
void CaptivePortalConnection::setQuery(char *query)
{
    this->query = query;
}

/**
 * @brief Set the SSID of the WiFi network
 * 
 * @param ssid WiFi network SSID
*/
void CaptivePortalConnection::setSSID(char *ssid)
{
    this->ssid = ssid;
}

/**
 * @brief Get the SSID of the WiFi network
 * @return char* ssid: WiFi network SSID
*/
char *CaptivePortalConnection::getSSID()
{
    return this->ssid;
}

/**
 * @brief Get the captive portal domain
 * @return char* captivePortalDomain: URL or IP of the radius server
*/
char *CaptivePortalConnection::getCaptive()
{
    return this->captivePortalDomain;
}

/**
 * @brief Get the query for the radius server
 * @return char* query: Usually a POST request
*/
char *CaptivePortalConnection::getQuery()
{
    return this->query;
}