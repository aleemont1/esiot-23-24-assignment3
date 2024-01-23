package org.mqttserver.presentation;


/*
* This class represent the message received by River monitoring service.
*
* The sensor just send THE WL (WaterLevel) data and an ID for the message.
* */
public class MessageFromSensor {

    private int WL;

    private int ID;

    public MessageFromSensor(int WL, int ID) {
        this.WL = WL;
        this.ID = ID;
    }

    public int getWL() {
        return WL;
    }

    public void setWL(int WL) {
        this.WL = WL;
    }

    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }
}
