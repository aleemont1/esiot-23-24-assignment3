package org.mqttserver;

import org.mqttserver.services.MQTT.Broker;
import org.mqttserver.services.MQTT.BrokerImpl;

public class Main {
    public static void main(String[] args) {
        System.out.println("Welcome in Smart River Monitoring Server...");
        Broker broker = new BrokerImpl();
        broker.initialize(broker.getMqttServer());
    }
}