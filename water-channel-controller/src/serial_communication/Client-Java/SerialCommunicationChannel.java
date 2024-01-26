package serial_communication.Client;
import javax.naming.CommunicationException;

/**
 * This is an interface that represents a communication channel between a client
 * and a server over a serial port.
 * It defines methods for processing received messages, sending messages,
 * checking if a message is available, and closing the communication channel.
 */
public interface SerialCommunicationChannel {

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
    public String processReceivedMessage(String messageToProcess) throws InterruptedException;

    /**
     * Sends a message to the server.
     * This method should be called by the client to send a message to the server.
     * 
     * @param messageToSend the message to send to the server.
     * @throws CommunicationException if there is a problem sending the message to
     *                                the server.
     */
    public void sendMessage(String messageToSend) throws CommunicationException;

    /**
     * Checks if a message is available on the serial port to be read by the client.
     * This method should be called by the client to check if a message is available
     * on the serial port.
     * 
     * @return true if a message is available, false otherwise.
     */
    boolean isMessageAvailable();

    /**
     * Closes the communication channel.
     * This method should be called by the client to close the communication channel
     * with the server.
     */
    public void close();

}