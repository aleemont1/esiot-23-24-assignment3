package org.mqttserver.presentation;


/*
* This class model the message to send to Arduino.
* */
public class MessageToArduino {

    private Statuses status;

    public MessageToArduino(Statuses status) {
        this.status = status;
    }

    public Statuses getStatus() {
        return this.status;
    }

    public void setStatus(Statuses status) {
        this.status = status;
    }
}
