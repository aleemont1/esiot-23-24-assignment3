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
            case ALARM_TOO_LOW -> "ALARM TOO LOW";
            case NORMAL -> "NORMAL";
            case PRE_ALARM_TOO_HIGH -> "PRE-ALARM TOO HIGH";
            case ALARM_TOO_HIGH -> "ALARM TOO HIGH";
            case ALARM_TOO_HIGH_CRITIC -> "ALARM TOO HIGH (CRITICAL)";
            case INVALID_STATUS -> "INVALID STATUS";
            default -> throw new IllegalArgumentException("Illegal status: " + this);
        };
    }
}
