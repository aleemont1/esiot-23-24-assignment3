package org.mqttserver.policy;

import io.vertx.core.buffer.Buffer;
import org.mqttserver.presentation.Status;
import org.mqttserver.services.MQTT.Broker;

import java.util.Map;

public interface SystemController {

    void setWL(float wl);

    Status getStatus();

    Map<Status, Integer> getStatusValveValue();

    int getFrequency();

    void checkValveValue(String msg, Broker broker);
}
