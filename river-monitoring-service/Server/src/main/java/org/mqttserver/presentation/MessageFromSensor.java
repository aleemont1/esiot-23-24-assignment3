package org.mqttserver.presentation;


/*
 * This class represent the message received by River monitoring service.
 *
 * The sensor just send THE WL (WaterLevel)
 * */
public class MessageFromSensor {
    private float WL;

    public MessageFromSensor(float WL) {
        this.WL = WL;
    }

    public float getWL() {
        return WL;
    }

    public void setWL(float WL) {
        this.WL = WL;
    }

}
