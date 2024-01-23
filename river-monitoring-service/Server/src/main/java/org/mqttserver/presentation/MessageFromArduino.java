package org.mqttserver.presentation;

public class MessageFromArduino {
    private int valvValue = 0;

    private String status = "";

    public MessageFromArduino(int valvValue, String status) {
        this.valvValue = valvValue;
        this.status = status;
    }

    public int getValvValue() {
        return valvValue;
    }

    public void setValvValue(int valvValue) {
        this.valvValue = valvValue;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
