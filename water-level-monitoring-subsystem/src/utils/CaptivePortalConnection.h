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
    CaptivePortalConnection();
    ~CaptivePortalConnection() = default;
    CaptivePortalConnection(char *ssid, char *captivePortalDomain, char *query);
    void setup_wifi() override;
    void setSSID(char *ssid) override;
    char *getSSID() override;
    void setCaptive(char *captivePortalDomain); // URL or IP of the radius server
    void setQuery(char *query);                 // Usually a POST request
    char *getCaptive();
    char *getQuery();

private:
    char *captivePortalDomain;
    char *query;
};

#endif // CAPTIVE_PORTAL_CONNECTION_H