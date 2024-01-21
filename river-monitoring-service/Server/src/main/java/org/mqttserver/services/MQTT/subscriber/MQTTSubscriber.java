package org.mqttserver.services.MQTT.subscriber;

import io.vertx.core.Handler;
import io.vertx.mqtt.MqttException;

public interface MQTTSubscriber {
    void subscribe(String topic, Handler<String> messageHandler);
}
