package org.mqttserver.serial;

public interface SerialReader {

    String readDataFromSerial();

    void closePort();
}
