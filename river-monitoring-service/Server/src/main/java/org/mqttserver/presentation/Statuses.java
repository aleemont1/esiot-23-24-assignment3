package org.mqttserver.presentation;

/**
 * This enum represents the statuses of the system*/
public enum Statuses {

    ALARM_TOO_LOW,
    NORMAL,
    PRE_ALARM_TOO_HIGH,
    ALARM_TOO_HIGH,
    ALARM_TOO_HIGH_CRITIC;


    @Override
    public String toString() {
        switch (this) {
            case ALARM_TOO_LOW:
                return "Alarm Too Low";
            case NORMAL:
                return "Normal";
            case PRE_ALARM_TOO_HIGH:
                return "Pre-Alarm Too High";
            case ALARM_TOO_HIGH:
                return "Alarm Too High";
            case ALARM_TOO_HIGH_CRITIC:
                return "Alarm Too High (Critical)";
            default:
                throw new IllegalArgumentException("Illegal status: " + this);
        }
    }
}
