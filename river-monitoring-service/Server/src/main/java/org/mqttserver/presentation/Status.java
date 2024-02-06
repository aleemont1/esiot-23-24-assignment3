package org.mqttserver.presentation;

/**
 * This enum represents the statuses of the system*/
public enum Status {

    ALARM_TOO_LOW,
    NORMAL,
    PRE_ALARM_TOO_HIGH,
    ALARM_TOO_HIGH,
    ALARM_TOO_HIGH_CRITIC,
    INVALID_STATUS;


    @Override
    public String toString() {
        return switch (this) {
            case ALARM_TOO_LOW -> "Alarm Too Low";
            case NORMAL -> "Normal";
            case PRE_ALARM_TOO_HIGH -> "Pre-Alarm Too High";
            case ALARM_TOO_HIGH -> "Alarm Too High";
            case ALARM_TOO_HIGH_CRITIC -> "Alarm Too High (Critical)";
            case INVALID_STATUS -> "Invalid Status";
            default -> throw new IllegalArgumentException("Illegal status: " + this);
        };
    }
}
