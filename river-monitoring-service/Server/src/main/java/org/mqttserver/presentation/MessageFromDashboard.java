package org.mqttserver.presentation;


/*The message sent by Dashboard using POST method in HTTP Server*/

public class MessageFromDashboard {
    private final int valveValue;

    public MessageFromDashboard(int valveValue) {
        this.valveValue = valveValue;
    }
    public int getValveValue() {
        return valveValue;
    }

}
