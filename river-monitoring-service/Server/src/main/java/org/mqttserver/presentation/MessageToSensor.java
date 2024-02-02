package org.mqttserver.presentation;


/**
 *
 * The river monitoring service send to the sensor just the frequence of measurement
 */


public class MessageToSensor {
    private int freq;

    public MessageToSensor(int freq) {
        this.freq = freq;
    }

    public int getFreq() {
        return freq;
    }

    public void setFreq(int freq) {
        this.freq = freq;
    }
}
