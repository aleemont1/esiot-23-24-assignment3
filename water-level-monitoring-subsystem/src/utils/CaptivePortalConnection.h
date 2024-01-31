// CaptivePortalConnection.h
#ifndef CAPTIVE_PORTAL_CONNECTION_H
#define CAPTIVE_PORTAL_CONNECTION_H

#include "IWifiConnection.h"

/**
 * @brief CaptivePortalConnection class
 * Connect to a free wifi with Captive Portal authentication.
 */
class CaptivePortalConnection : public IWifiConnection
{
public:
    /**
     * @brief Construct a new CaptivePortalConnection object
     *
     * Default values for ssid, captivePortalDomain and query are used
     * (see \ref ../constants.h)
     *
     */
    CaptivePortalConnection();

    ~CaptivePortalConnection() = default;

    /**
     *
     * @brief Construct a new CaptivePortalConnection object
     * @param ssid WiFi network SSID
     * @param captivePortalDomain URL or IP of the radius server
     * @param query Usually a POST request
     *
     */
    CaptivePortalConnection(char *ssid, char *captivePortalDomain, char *query);

    /**
     * @brief Initialize WiFi connection
     *
     */
    void setup_wifi() override;

    /**
     * @brief Set the SSID of the WiFi network
     *
     * @param ssid WiFi network SSID
     */
    void setSSID(char *ssid) override;

    /**
     * @brief Get the SSID of the WiFi network
     * @return char* ssid: WiFi network SSID
     */
    char *getSSID() override;

    /**
     * @brief Set the captive portal domain
     *
     * @param captivePortalDomain URL or IP of the radius server
     *
     */
    void setCaptive(char *captivePortalDomain); // URL or IP of the radius server

    /**
     * @brief Get the captive portal domain
     * @return char* captivePortalDomain: URL or IP of the radius server
     */
    char *getCaptive();

    /**
     * @brief Set the query for the radius server
     *
     * @param query Usually a POST request
     */
    void setQuery(char *query); // Usually a POST request

    /**
     * @brief Get the query for the radius server
     * @return char* query: Usually a POST request
     */
    char *getQuery();

private:
    char *captivePortalDomain;
    char *query;
};

#endif // CAPTIVE_PORTAL_CONNECTION_H