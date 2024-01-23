package org.mqttserver.services.MQTT;

import io.vertx.mqtt.MqttServer;

public interface Broker {
    void initialize(MqttServer mqttServer);
    MqttServer getMqttServer();

}
