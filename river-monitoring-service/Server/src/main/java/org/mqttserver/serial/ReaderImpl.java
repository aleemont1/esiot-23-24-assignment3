package org.mqttserver.serial;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;
import org.mqttserver.presentation.JSONUtils;
import org.mqttserver.presentation.SerialMessage;


public class ReaderImpl implements Runnable { //builded as new Runnable thread

    private static SerialPort serialPort;

    private void initCOMPort() throws SerialPortException {
        try {
            SerialScanner serialScanner = new SerialScannerImpl();
            serialPort = new SerialPort(serialScanner.getConnectedPort());
            serialPort.openPort();
            serialPort.setParams(9600, 8, 1, SerialPort.PARITY_NONE);
            serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT);
            serialPort.addEventListener(new PortReader(), SerialPort.MASK_RXCHAR);
        }
        catch (SerialPortException ex) {
            System.out.println(ex);
        }
    }

    @Override
    public void run() {
        try {
            initCOMPort();
        } catch (SerialPortException e) {
            throw new RuntimeException(e);
        }
    }

    private class PortReader implements SerialPortEventListener {
        StringBuilder string = new StringBuilder();
        @Override
        public void serialEvent(SerialPortEvent event) {
            if (event.isRXCHAR() && event.getEventValue() > 0) {
                try {
                    byte[] receivedData = serialPort.readBytes(event.getEventValue());
                    for (byte b : receivedData) {
                        char receivedChar = (char) b;
                        string.append(receivedChar);
                        if (receivedChar == '\n') {
                            String jsonString = string.toString();
                            try {
                                jsonString = jsonString.replace(" ", "");
                                SerialMessage serialMessage = JSONUtils.jsonToObject(jsonString, SerialMessage.class);
                                System.out.println(serialMessage.getNumber());
                            } catch (Exception e) {
                                System.out.println("Error in JSON conversion");
                            }
                            string.setLength(0);
                        }
                    }
                } catch (SerialPortException ex) {
                    System.out.println("Error in receiving response from port: " + ex);
                }
            }
        }
    }
}