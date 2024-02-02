package org.mqttserver.policy;

import org.mqttserver.presentation.Status;

public interface SystemController {

    void setWL(float wl);

    Status getStatus();

}
