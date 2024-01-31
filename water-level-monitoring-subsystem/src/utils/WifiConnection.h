// WifiConnection.h
#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include "IWifiConnection.h"

/**
 * @brief WifiConnection class
 * Connect to a wifi network, with or without password.
 */
class WifiConnection : public IWifiConnection
{
public:

    /**
     * @brief Construct a new WifiConnection object
     *
     * Default values for ssid are used
     * (see \ref ../constants.h)
     *
     */
    WifiConnection();

    /**
     * @brief Construct a new WifiConnection object
     * @param ssid WiFi network SSID
     */
    WifiConnection(char *ssid);

    /**
     * @brief Construct a new WifiConnection object
     * @param ssid WiFi network SSID
     * @param password WiFi network password
     */
    WifiConnection(char *ssid, char *password);
    ~WifiConnection() = default;

    /**
     * @brief Initialize WiFi connection
     *
     */
    void setup_wifi() override;

    /**
     * @brief Set the SSID object
     * @param ssid WiFi network SSID
     */
    void setSSID(char *ssid) override;

    /**
     * @brief Get the SSID object
     * @return char* ssid: WiFi network SSID
     */
    char *getSSID() override;

    /**
     * @brief Set the Password object
     * @param password WiFi network password
     */
    void setPassword(char *password);

private:
    char *ssid;
    char *password;
};

#endif // WIFI_CONNECTION_H
