package org.mqttserver.presentation;


/**
 *
 * The river monitoring service send to the sensor just the frequence of measurement
 */


public class MessageToSensor {
    /**
     * The frequency of measurements to be set for the sensor.
     */
    private String freq;

    /**
     * Constructs a MessageToSensor object with the specified frequency.
     *
     * @param freq The frequency of measurements to be set for the sensor.
     */
    public MessageToSensor(String freq) {
        this.freq = freq;
    }

    /**
     * Gets the frequency of measurements.
     *
     * @return The frequency of measurements set for the sensor.
     */
    public String getFreq() {
        return freq;
    }

    /**
     * Sets the frequency of measurements.
     *
     * @param freq The frequency of measurements to be set for the sensor.
     */
    public void setFreq(String freq) {
        this.freq = freq;
    }
}
