package org.mqttserver.serial;

import jssc.SerialPort;
import jssc.SerialPortException;

public class WriterImpl implements Writer {

    private SerialPort serialPort;
    public WriterImpl() {
        SerialScanner serialScanner = new SerialScannerImpl();
        String connectedPort = serialScanner.getConnectedPort();
        //ReaderImpl.closePort();

        this.serialPort = new SerialPort(connectedPort);

        try {
            serialPort.openPort();
            serialPort.setParams(SerialPort.BAUDRATE_9600, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
        } catch (SerialPortException e) {
            System.err.println("Error in OPENING Serial Line");
        }
    }

    @Override
    public void writeDataOnSerial(String message) {
        try {
            System.out.println("SONO QUI DOVREI SCRIVERE " + message );
            serialPort.writeBytes(message.getBytes());
        } catch (SerialPortException e) {
            System.err.println("Error in WRITING Serial Line");
        }
    }

}
