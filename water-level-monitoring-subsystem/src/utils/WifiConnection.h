// WifiConnection.h
#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include "IWifiConnection.h"

class WifiConnection : public IWifiConnection {
public:
    WifiConnection() = default;
    ~WifiConnection() = default;
    void setup_wifi() override;
};

#endif // WIFI_CONNECTION_H