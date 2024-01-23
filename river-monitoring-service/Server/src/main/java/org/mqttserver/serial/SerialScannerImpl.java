package org.mqttserver.serial;

import jssc.SerialPortList;
public class SerialScannerImpl implements SerialScanner {

    public SerialScannerImpl() {

    }

    @Override
    public String getConnectedPort() {
        String[] portNames = SerialPortList.getPortNames();
        String connectedPort = "";

        for (String portName : portNames) {
            System.out.println(portName + " Available!");
            connectedPort = portName;
        }
        return connectedPort;
    }
}
