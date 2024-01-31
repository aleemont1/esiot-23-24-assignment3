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
    WifiConnection();
    WifiConnection(char *ssid);
    WifiConnection(char *ssid, char *password);
    ~WifiConnection() = default;
    void setup_wifi() override;
    void setSSID(char *ssid) override;
    char *getSSID() override;
    void setPassword(char *password);

private:
    char *ssid;
    char *password;
};

#endif // WIFI_CONNECTION_H
