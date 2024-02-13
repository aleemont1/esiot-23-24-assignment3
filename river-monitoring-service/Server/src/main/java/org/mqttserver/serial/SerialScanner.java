package org.mqttserver.serial;
/**
 * Implementing classes should provide functionality to identify and retrieve information about connected serial ports.
 */
public interface SerialScanner {

    /**
     * Gets the identifier of the currently connected serial port.
     *
     * @return A string representing the identifier of the connected serial port. (OM3, COM4)
     */
    String getConnectedPort();
}