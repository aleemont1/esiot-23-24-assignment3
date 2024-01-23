package org.mqttserver.presentation;


/**
 *
 * The river monitoring service send to the sensor just the frequence of measurement
 */


public class MessageToSensor {
    private int frequency;

    public MessageToSensor(int frequency) {
        this.frequency = frequency;
    }

    public int getFrequency() {
        return frequency;
    }

    public void setFrequency(int frequency) {
        this.frequency = frequency;
    }
}
