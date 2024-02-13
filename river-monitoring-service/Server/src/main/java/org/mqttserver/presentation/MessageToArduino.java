package org.mqttserver.presentation;


/*
 * This class model the message to send to Arduino.
 * */
public class MessageToArduino {

    private Status status;

    private int valveValue = -1;

    public MessageToArduino(Status status) {
        this.status = status;
    }

    public MessageToArduino(int valveValue) {
        this.valveValue = valveValue;
    }

    public Status getStatus() {
        return this.status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    public void setValveValue(int valveValue) {
        this.valveValue = valveValue;
    }
}
