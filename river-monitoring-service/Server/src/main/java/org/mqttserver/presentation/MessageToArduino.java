package org.mqttserver.presentation;


/*
* This class model the message to send to Arduino.
* */
public class MessageToArduino {

    private Status status;

    public MessageToArduino(Status status) {
        this.status = status;
    }

    public Status getStatus() {
        return this.status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }
}
