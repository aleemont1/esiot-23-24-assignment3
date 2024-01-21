package org.mqttserver.services.MQTT;

import io.vertx.mqtt.MqttServer;

public interface Broker {
    boolean initialize(MqttServer mqttServer);
    MqttServer getMqttServer();

}
