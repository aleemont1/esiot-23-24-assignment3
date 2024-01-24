package org.mqttserver.serial;

public interface SerialWriter {
    void writeDataOnSerial(String message);
}
