package serial_communication.Client;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import javax.naming.CommunicationException;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

/**
 * This class implementation represents a communication channel between a client
 * and a server over a serial port.
 * It uses the jSSC (Java Simple Serial Connector) library to handle the serial
 * communication.
 */
public class SerialCommunicationChannelImpl implements SerialCommunicationChannel, SerialPortEventListener {

    /**
     * The serial port used for the communication.
     */
    private SerialPort serialPort;
    /**
     * The queue of messages received from the server.
     */
    private BlockingQueue<String> messageQueue;
    /**
     * The current message being received from the server.
     */
    private StringBuffer currentMessage = new StringBuffer("");

    /**
     * Constructs a new with the specified serial port and rate.
     * 
     * @param serialPort The serial port to use for the communication.
     * @param rate       The baud rate of the serial port.
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

    /**
     * Processes a message received from the server.
     * This method should be called by the client when a message is received from
     * the server.
     * 
     * @param messageToProcess the message received from the server.
     * @return the processed message received from the server.
     * @throws InterruptedException if the thread is interrupted while processing
     *                              the message.
     */
    @Override
    public String processReceivedMessage(String messageToProcess) throws InterruptedException {
        return messageQueue.take();
    }

    /**
     * Sends a message to the server.
     * This method should be called by the client to send a message to the server.
     * 
     * @param messageToSend the message to send to the server.
     * @throws CommunicationException if there is a problem sending the message to
     *                                the server.
     */
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

    /**
     * Checks if a message is available on the serial port to be read by the client.
     * This method should be called by the client to check if a message is available
     * on the serial port.
     * 
     * @return true if a message is available, {@code false} otherwise.
     */
    @Override
    public boolean isMessageAvailable() {
        return !messageQueue.isEmpty();
    }

    /**
     * Closes the communication channel.
     * This method should be called by the client to close the communication channel
     * with the server.
     */
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

    /**
     * Handles a serial port event.
     * This method is called by the jSSC library when a serial port event occurs,
     * such as receiving data.
     * 
     * @param event the serial port event.
     */
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