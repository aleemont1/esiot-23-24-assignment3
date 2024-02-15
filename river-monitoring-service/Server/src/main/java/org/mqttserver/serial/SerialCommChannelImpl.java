package org.mqttserver.serial;

import java.util.concurrent.*;

import jssc.*;

public class SerialCommChannelImpl implements SerialCommChannel, SerialPortEventListener {

    private final SerialPort serialPort;
    private final BlockingQueue<String> queue;
    private StringBuffer currentMsg = new StringBuffer("");

    public SerialCommChannelImpl(String port, int rate) throws Exception {
        queue = new ArrayBlockingQueue<String>(200);
        serialPort = new SerialPort(port);
        serialPort.openPort();
        serialPort.setParams(rate,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);
        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
                SerialPort.FLOWCONTROL_RTSCTS_OUT);
        // serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
        serialPort.addEventListener(this);
    }

    @Override
    public void sendMessageToArduino(String msg) {
        char[] array = (msg + "\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            bytes[i] = (byte) array[i];
        }
        try {
            synchronized (serialPort) {
                System.out.println("Server wrote on arduino: " + String.valueOf(array));
                serialPort.writeBytes(bytes);
            }
        } catch (Exception ex) {
            System.err.println("Exception in writing serial line");
        }
    }

    @Override
    public String receiveMessageFromArduino() throws InterruptedException {
        if (isMsgAvailable()) {
            return queue.take() ;
        }
        return "Failed to retrieve data from Arduino";

    }

    @Override
    public boolean isMsgAvailable() {
        return !queue.isEmpty();
    }

    public void close() {
        try {
            if (serialPort != null) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }


    /**
     * Handle the event on serial line when a message is received.
     */
    public void serialEvent(SerialPortEvent event) {

        if (event.isRXCHAR()) {
            try {
                String msg = serialPort.readString(event.getEventValue());
                msg = msg.replaceAll("\r", "");
                currentMsg.append(msg);
                boolean goAhead = true;
                while (goAhead) {
                    String msg2 = currentMsg.toString();
                    int index = msg2.indexOf("\n");
                    if (index >= 0) {
                        queue.put(msg2.substring(0, index));
                        currentMsg = new StringBuffer("");
                        if (index + 1 < msg2.length()) {
                            currentMsg.append(msg2.substring(index + 1));
                        }
                    } else {
                        goAhead = false;
                    }
                }




            } catch (Exception ex) {
                ex.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + ex);
            }


        }
    }
}
