// IWifiConnection.h
#ifndef IWIFI_CONNECTION_H
#define IWIFI_CONNECTION_H

/**
 * @brief Interface for WiFi connection
 * 
 */
class IWifiConnection
{
public:
  virtual ~IWifiConnection() = default;
  virtual void setup_wifi() = 0;
  virtual void setSSID(const char *ssid) = 0;
  virtual const char *getSSID() = 0;
  virtual int status() = 0;

protected:
  const char *ssid;
};

#endif // IWIFI_CONNECTION_H