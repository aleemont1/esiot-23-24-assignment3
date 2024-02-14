package org.mqttserver.presentation;

/**
 * This class model the message received from Arduino
 */

public class MessageFromArduino {

    private String status = "";
    private Integer valveValue = 0;

    public MessageFromArduino(Integer valveValue, String status) {
        this.valveValue = valveValue;
        this.status = status;
    }

    public Integer getValveValue() {
        return valveValue;
    }

    public void setValveValue(Integer valveValue) {
        this.valveValue = valveValue;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
