package org.mqttserver.policy;

import io.vertx.core.buffer.Buffer;
import org.mqttserver.presentation.JSONUtils;
import org.mqttserver.presentation.MessageFromArduino;
import org.mqttserver.presentation.Status;
import org.mqttserver.services.MQTT.Broker;

import java.util.HashMap;
import java.util.Map;

public class SystemControllerImpl implements SystemController {

    private Status status;

    private final double WL1 = 5;
    private final double WL2 = 20;
    private final double WL3 = 25;
    private final double WL4 = 28;

    private int frequency = 1;

    private final int F1 = 1800; //1800ms

    private final int F2 = 1000; //1000ms


    private final Map<Status, Integer> statusValveValue = new HashMap<Status, Integer>() {{
        put(Status.ALARM_TOO_LOW, 0);
        put(Status.NORMAL, 25 );
        put(Status.PRE_ALARM_TOO_HIGH, 40 );
        put(Status.ALARM_TOO_HIGH, 50);
        put(Status.ALARM_TOO_HIGH_CRITIC, 100);
    }};

    private final Map<Status, Integer> statusFreq = new HashMap<Status, Integer>() {{
        put(Status.ALARM_TOO_LOW, F2);
        put(Status.NORMAL, F1 );
        put(Status.PRE_ALARM_TOO_HIGH, F2 );
        put(Status.ALARM_TOO_HIGH, F2);
        put(Status.ALARM_TOO_HIGH_CRITIC, F2);
    }};



    public SystemControllerImpl() {

    }

    @Override
    public void setWL(float wl) {
        if (wl < WL1) {
            this.status = Status.ALARM_TOO_LOW;
        } else if (wl > WL1 && wl <= WL2) {
            this.status = Status.NORMAL;
        } else if (wl > WL2 ) {
            if (wl > WL2 && wl <= WL3 ) {
                this.status = Status.PRE_ALARM_TOO_HIGH;
            } else if (wl > WL3 && wl <= WL4) {
                this.status = Status.ALARM_TOO_HIGH;
            }
        } else if (wl > WL4) {
            this.status = Status.ALARM_TOO_HIGH_CRITIC;
        }

        this.frequency = this.statusFreq.get(this.status);
        System.out.println("SET SYSTEM STATUS: " + this.status);
        System.out.println("SET SYSTEM FREQ: " + this.frequency);
    }

    public Status getStatus() {
        return this.status;
    }

    public Map<Status, Integer> getStatusValveValue() {
        return this.statusValveValue;
    }

    @Override
    public int getFrequency() {
        return this.frequency;
    }

    @Override
    public void checkValveValue(String msg, Broker broker) {
        try {
            System.out.println("ARDUINO SENT: " + msg);
            Integer valveValue = JSONUtils.jsonToObject(msg, MessageFromArduino.class).getValveValue();
            if (valveValue.equals(broker.getSystemController().getStatusValveValue().get(broker.getSystemController().getStatus()))) {
                System.out.println("SERVER: Valve value ok");
            } else {
                System.err.println("SERVER: Valve value incorrect for system state");
            }
        } catch (Exception ex) {
            System.err.println("Il server è In attesa di dati validi da parte di Arduino....");
        }
    }
}
