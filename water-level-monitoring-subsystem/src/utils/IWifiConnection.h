// IWifiConnection.h
#ifndef IWIFI_CONNECTION_H
#define IWIFI_CONNECTION_H

class IWifiConnection
{
public:
  virtual ~IWifiConnection() = default;
  virtual void setup_wifi() = 0;
  virtual void setSSID(char *ssid) = 0;
  virtual char *getSSID() = 0;

protected:
  char *ssid;
};

#endif // IWIFI_CONNECTION_H