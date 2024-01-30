// IWifiConnection.h
#ifndef IWIFI_CONNECTION_H
#define IWIFI_CONNECTION_H

class IWifiConnection {
public:
    virtual ~IWifiConnection() = default;
    virtual void setup_wifi() = 0;
};

#endif // IWIFI_CONNECTION_H