package org.mqttserver.serial;


/**
 * Interface for serial communication with Arduino.
 */
public interface SerialCommChannel {

	/**
	 * Sends a message to the Arduino through the serial channel.
	 *
	 * @param message The message to be sent to the Arduino.
	 */
	void sendMessageToArduino(String message);

	/**
	 * Receives a message from the Arduino through the serial channel.
	 *
	 * @return The message received from the Arduino.
	 * @throws InterruptedException If the receiving operation is interrupted.
	 */
	String receiveMessageFromArduino() throws InterruptedException;

	/**
	 * Checks if there are messages available for reading from the serial channel.
	 *
	 * @return True if there are available messages, otherwise False.
	 */
	boolean isMsgAvailable();
}
