package org.mqttserver.policy;

import io.vertx.core.buffer.Buffer;
import org.mqttserver.presentation.JSONUtils;
import org.mqttserver.presentation.MessageFromArduino;
import org.mqttserver.presentation.MessageToArduino;
import org.mqttserver.presentation.Status;
import org.mqttserver.services.MQTT.Broker;

import java.util.HashMap;
import java.util.Map;

public class SystemControllerImpl implements SystemController {

    private final double WL1 = 5;
    private final double WL2 = 20;
    private final double WL3 = 25;
    private final double WL4 = 28;
    private final double INVALID_WL = -1;
    private final int F1 = 6000; //1800ms
    private final int F2 = 2000; //1000ms
    private final int F0 = 0;
    private Status status = null;
    private int valveValue = 0;
    private float wl = 0;
    private boolean isManual = false;
    private int frequency = 1;
    private final int V0= 0;
    private final int V1= 25;
    private final int V2= 40;
    private final int V3= 50;
    private final int V4 = 100;

    private final Map<Status, Integer> statusValveValue = new HashMap<Status, Integer>() {{
        put(Status.ALARM_TOO_LOW, V0);
        put(Status.NORMAL, V1);
        put(Status.PRE_ALARM_TOO_HIGH, V2);
        put(Status.ALARM_TOO_HIGH, V3);
        put(Status.ALARM_TOO_HIGH_CRITIC, V4);
    }};
    private final Map<Status, Integer> statusFreq = new HashMap<Status, Integer>() {{
        put(Status.ALARM_TOO_LOW, F2);
        put(Status.NORMAL, F1);
        put(Status.PRE_ALARM_TOO_HIGH, F2);
        put(Status.ALARM_TOO_HIGH, F2);
        put(Status.ALARM_TOO_HIGH_CRITIC, F2);
        put(Status.INVALID_STATUS, F0);
    }};


    public SystemControllerImpl() {

    }

    @Override
    public void setWL(float wl) {
        System.out.println("WL RECEIVED VALUE: " + wl);
        if (wl > INVALID_WL) { //INVALID WL = -1;
            this.wl = wl;
            if (wl < WL1) {
                this.status = Status.ALARM_TOO_LOW;
            } else if (wl > WL1 && wl <= WL2) {
                this.status = Status.NORMAL;
            } else if (wl > WL2) {
                if (wl > WL2 && wl <= WL3) {
                    this.status = Status.PRE_ALARM_TOO_HIGH;
                } else if (wl > WL3 && wl <= WL4) {
                    this.status = Status.ALARM_TOO_HIGH;
                }
            } else if (wl > WL4) {
                this.status = Status.ALARM_TOO_HIGH_CRITIC;
            }
            this.frequency = this.statusFreq.get(this.status);
            System.out.println("SET SYSTEM FREQ: " + this.frequency);
        } else {
            this.status = Status.INVALID_STATUS;
        }
        System.out.println("SET SYSTEM STATUS: " + this.status.toString().toUpperCase());
    }

    public Status getStatus() {
        if (this.status == null) {
            System.err.println("SERVER: STATUS undefined, check your connection to sensor");
            return null;
        }
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
    public float getWl() {
        return this.wl;
    }

    @Override
    public int getValveValue() {
        return this.valveValue;
    }

    @Override
    public void setValveValueFromDashboard(int valveValue) {
        this.valveValue = valveValue;
    }

    @Override
    public void checkValveValue(String msg, Broker broker) {
        try {
            System.out.println("ARDUINO SENT: " + msg);
            Integer valveValue = JSONUtils.jsonToObject(msg, MessageFromArduino.class).getValveValue();
            if (valveValue.equals(broker.getSystemController().getStatusValveValue().get(broker.getSystemController().getStatus()))) {
                System.out.println("SERVER: Valve value ok");
                this.valveValue = valveValue;
            } else {
                System.err.println("SERVER: Valve value incorrect for system state");
            }
        } catch (Exception ex) {
            System.err.println("Il server è In attesa di dati validi da parte di Arduino....");
        }
    }

    @Override
    public boolean getIsManual() {
        return this.isManual;
    }

    @Override
    public void setIsManual(boolean isManual) {
        this.isManual = isManual;
    }


}
