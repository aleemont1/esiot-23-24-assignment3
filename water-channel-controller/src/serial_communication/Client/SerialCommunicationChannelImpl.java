package serial_communication.Client;

import javax.naming.CommunicationException;
import java.util.concurrent.*;
import jssc.*;

/**
 * Implementation of the communication channel between client and server on the
 * serial port.
 */
public class SerialCommunicationChannelImpl implements SerialCommunicationChannel, SerialPortEventListener {

    private SerialPort serialPort;
    private BlockingQueue<String> messageQueue;
    private StringBuffer currentMessage = new StringBuffer("");

    /**
     * Constructor of the class SerialCommunicationChannelImpl.
     * 
     * @param serialPort The serial port to use for the communication.
     * @param rate       The rate of the serial port.
     * @throws CommunicationException If the communication channel cannot be opened.
     * @throws SerialPortException    If the serial port cannot be opened.
     */
    public SerialCommunicationChannelImpl(SerialPort serialPort, int rate)
            throws CommunicationException, SerialPortException {
        this.serialPort = new SerialPort(serialPort.getPortName());
        this.messageQueue = new LinkedBlockingQueue<String>();
        this.serialPort.openPort();
        this.serialPort.setParams(rate, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
        this.serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT);
        this.serialPort.addEventListener(this);
    }

    @Override
    public String processReceivedMessage(String messageToProcess) throws InterruptedException {
        return messageQueue.take();
    }

    @Override
    public void sendMessage(String messageToSend) throws CommunicationException {
        char[] message = (messageToSend + "\n").toCharArray();
        byte[] messageBytes = new byte[message.length];
        for (int i = 0; i < messageBytes.length; i++) {
            messageBytes[i] = (byte) message[i];
        }
        try {
            synchronized (this.serialPort) {
                this.serialPort.writeBytes(messageBytes);
            }
        } catch (SerialPortException exception) {
            exception.printStackTrace();
            throw new CommunicationException("Error while sending message from client to server");
        }
    }

    @Override
    public boolean isMessageAvailable() {
        return !messageQueue.isEmpty();
    }

    @Override
    public void close() {
        try {
            if (this.serialPort.isOpened()) {
                this.serialPort.removeEventListener();
                this.serialPort.closePort();
            }
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        if (event.isRXCHAR()) {
            try {
                String message = serialPort.readString(event.getEventValue());
                message = message.replaceAll("\r", "");
                currentMessage.append(message);
                boolean goAhead = true;
                while (goAhead) {
                    String currentMessageString = currentMessage.toString();
                    int index = currentMessageString.indexOf("\n");
                    if (index >= 0) {
                        messageQueue.put(currentMessageString.substring(0, index));
                        currentMessage = new StringBuffer("");
                        if (index + 1 < currentMessageString.length()) {
                            currentMessage.append(currentMessageString.substring(index + 1));
                        }
                    } else {
                        goAhead = false;
                    }
                }
            } catch (SerialPortException exception) {
                exception.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + exception);
            } catch (InterruptedException exception) {
                exception.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + exception);
            }
        }
    }
}