// WifiConnection.h
#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include "IWifiConnection.h"

/**
 * @brief WifiConnection class
 * Connect to a wifi network, with or without password.
 * @implements IWifiConnection
 * @extends IWifiConnection
 */
class WifiConnection : public IWifiConnection
{
public:

    /**
     * @brief Construct a new WifiConnection object
     *
     * Default values for ssid are used
     * (see \ref ../config.h)
     *
     */
    WifiConnection();

    /**
     * @brief Construct a new WifiConnection object
     * @param ssid WiFi network SSID
     */
    WifiConnection(const char *ssid);

    /**
     * @brief Construct a new WifiConnection object
     * @param ssid WiFi network SSID
     * @param password WiFi network password
     */
    WifiConnection(const char *ssid, const char *password);
    ~WifiConnection() = default;

    /**
     * @brief Initialize WiFi connection
     *
     */
    void setup_wifi() override;

    /**
     * @brief Set the SSID object.
     * @param ssid WiFi network SSID.
     */
    void setSSID(const char *ssid) override;

    /**
     * @brief Get the SSID object.
     * @return char* ssid: WiFi network SSID.
     */
    const char *getSSID() override;

    /**
     * @brief Set the Password object.
     * @param password WiFi network password.
     */
    void setPassword(const char *password);

    /**
     * @brief Check connection status (a \ref WiFi.status() wrapper).
     * @return int status: WiFi network status.
     */
    int status() override;

private:
    const char *password;
};

#endif // WIFI_CONNECTION_H
