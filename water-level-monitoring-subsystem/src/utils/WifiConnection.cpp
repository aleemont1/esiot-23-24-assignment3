#include "WifiConnection.h"
#include <WiFi.h>
#include "../env/constants.h"

/**
 * @brief Construct a new WifiConnection object
 *
 * Default values for ssid are used
 * (see \ref ../constants.h)
 *
 */
WifiConnection::WifiConnection()
{
    this->ssid = ssid;
    this->password = nullptr;
}

/**
 * @brief Construct a new WifiConnection object
 * @param ssid WiFi network SSID
 */
WifiConnection::WifiConnection(char *ssid)
{
    this->ssid = ssid;
    this->password = nullptr;
}

/**
 * @brief Construct a new WifiConnection object
 * @param ssid WiFi network SSID
 * @param password WiFi network password
 */
WifiConnection::WifiConnection(char *ssid, char *password)
{
    this->ssid = ssid;
    this->password = password;
}

/**
 * @brief Initialize WiFi connection
 *
 */
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

/**
 * @brief Set the SSID object
 * @param ssid WiFi network SSID
 */
void WifiConnection::setSSID(char *ssid)
{
    this->ssid = ssid;
}

/**
 * @brief Get the SSID object
 * @return char* ssid: WiFi network SSID
 */
char *WifiConnection::getSSID()
{
    return this->ssid;
}

/**
 * @brief Set the Password object
 * @param password WiFi network password
 */
void WifiConnection::setPassword(char *password)
{
    this->password = password;
}
