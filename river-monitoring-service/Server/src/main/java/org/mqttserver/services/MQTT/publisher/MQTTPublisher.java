package org.mqttserver.services.MQTT.publisher;

import io.vertx.mqtt.MqttException;

public interface MQTTPublisher {
    void publish(String topic, String message);


}
