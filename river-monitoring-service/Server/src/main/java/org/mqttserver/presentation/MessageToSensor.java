package org.mqttserver.presentation;


/**
 *
 * The river monitoring service send to the sensor just the frequence of measurement
 */


public class MessageToSensor {
    private String freq;

    public MessageToSensor(String freq) {
        this.freq = freq;
    }

    public String getFreq() {
        return freq;
    }

    public void setFreq(String freq) {
        this.freq = freq;
    }
}
