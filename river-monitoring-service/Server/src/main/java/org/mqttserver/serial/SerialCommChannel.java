package org.mqttserver.serial;

/**
 * Simple interface for an async msg communication channel
 * @author aricci
 *
 */
public interface SerialCommChannel {

	void sendMessageToArduino(String message);
	String receiveMessageFromArduino() throws InterruptedException;
	boolean isMsgAvailable();

}
