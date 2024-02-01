package org.mqttserver.policy;

import org.mqttserver.presentation.Status;

public class SystemControllerImpl implements SystemController {

    private Status status;

    private final double WL1 = 5;
    private final double WL2 = 20;
    private final double WL3 = 25;
    private final double WL4 = 28;

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
        System.out.println("SET SYSTEM STATUS: " + this.status + "\n\n");


    }

    public Status getStatus() {
        return this.status;
    }
}
