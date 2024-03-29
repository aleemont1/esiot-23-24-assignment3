// CaptivePortalConnection.h
#ifndef CAPTIVE_PORTAL_CONNECTION_H
#define CAPTIVE_PORTAL_CONNECTION_H

#include "IWifiConnection.h"

/**
 * @brief CaptivePortalConnection class.
 * Connect to a free wifi with Captive Portal authentication.
 * @implements IWifiConnection
 * @extends IWifiConnection
 */
class CaptivePortalConnection : public IWifiConnection
{
public:
    /**
     * @brief Construct a new CaptivePortalConnection object.
     *
     * Default values for ssid, captivePortalDomain and query are used
     * (see \ref ../config.h).
     *
     */
    CaptivePortalConnection();

    ~CaptivePortalConnection() = default;

    /**
     *
     * @brief Construct a new CaptivePortalConnection object.
     * @param ssid WiFi network SSID.
     * @param captivePortalDomain URL or IP of the radius server.
     * @param query Usually a POST request.
     *
     */
    CaptivePortalConnection(const char *ssid, const char *captivePortalDomain, const char *query);

    /**
     * @brief Initialize WiFi connection.
     *
     */
    void setup_wifi() override;

    /**
     * @brief Set the SSID of the WiFi network.
     *
     * @param ssid WiFi network SSID.
     */
    void setSSID(const char *ssid) override;

    /**
     * @brief Get the SSID of the WiFi network.
     * @return char* ssid: WiFi network SSID.
     */
    const char *getSSID() override;

    /**
     * @brief Set the captive portal domain.
     *
     * @param captivePortalDomain URL or IP of the radius server.
     *
     */
    void setCaptive(const char *captivePortalDomain);

    /**
     * @brief Get the captive portal domain.
     * @return char* captivePortalDomain: URL or IP of the radius server.
     */
    const char *getCaptive();

    /**
     * @brief Set the query for the radius server.
     *
     * @param query Usually a POST request.
     */
    void setQuery(const char *query);

    /**
     * @brief Get the query for the radius server.
     * @return char* query: Usually a POST request.
     */
    const char *getQuery();

    /**
     * @brief Check connection status (a \ref WiFi.status() wrapper).
     * @return int status: WiFi network status.
     */
    int status() override;

private:
    const char *captivePortalDomain;
    const char *query;
};

#endif // CAPTIVE_PORTAL_CONNECTION_H