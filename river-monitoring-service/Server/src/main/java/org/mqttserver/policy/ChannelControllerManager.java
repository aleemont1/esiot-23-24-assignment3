package org.mqttserver.policy;

import org.mqttserver.presentation.Status;

public interface ChannelControllerManager {

    //ARDUINO

    /**
     * @brief Sends a status message to Arduino.
     *
     * This function is used to send a status message to the Arduino.
     *
     * @param status A Status object representing the current status of the system
     */
    void sendMessageToArduino(Status status);

    /**
     * @brief Sends a manual valve value to Arduino.
     *
     * This function is used when a manual valve value is sent by the dashboard.
     * It takes an integer argument representing the valve value.
     *
     * @param valveValue An integer value representing the manual valve setting.
     */
    void sendMessageToArduino(int valveValue);

    /**
     * @brief Receives data from Arduino.
     *
     * This function is used to receive data from Arduino in serialLine
     * It returns a String containing the received data.
     *
     * @return A String containing the received data.
     * @throws InterruptedException if an error occurs during data reception.
     */
    String receiveDataFromArduino() throws InterruptedException;

}
