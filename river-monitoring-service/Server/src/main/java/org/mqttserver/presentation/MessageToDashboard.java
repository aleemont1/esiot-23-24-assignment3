package org.mqttserver.presentation;


public class MessageToDashboard {

    private float WL;
    private Status status;

    private int valveValue;

    public MessageToDashboard(float WL, Status status, int valveValue) {
        this.WL = WL;
        this.status = status;
        this.valveValue = valveValue;
    }

    public float getWL() {
        return WL;
    }

    public Status getStatus() {
        return status;
    }

    public int getValveValue() {
        return valveValue;
    }

}
