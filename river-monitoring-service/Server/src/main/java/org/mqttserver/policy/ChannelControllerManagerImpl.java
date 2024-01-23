package org.mqttserver.policy;

import io.vertx.mqtt.MqttServer;
import org.mqttserver.services.HTTP.HTTPServer;
import org.mqttserver.services.MQTT.Broker;
import org.mqttserver.services.MQTT.BrokerImpl;

import java.util.logging.Handler;

public class ChannelControllerManagerImpl implements ChannelControllerManager {


    private Broker broker;
    private HTTPServer httpServer = null;

    public ChannelControllerManagerImpl(Broker broker, HTTPServer httpServer) {
        this.broker = broker;
        this.httpServer = httpServer;
    }

    private void startController() {
        //TODO: here the implementation of starting
        System.out.println("Started CHANNEL CONTROLLER " + "\nChannel Controller Control MQTTServer: " +
                this.broker.getMqttServer().toString() + " ON PORT: "  + this.broker.getMqttServer().actualPort());
    }

    @Override
    public void sendMessageToArduino(String message) { //USE SERIAL LINE

    }

    @Override
    public void sendMessageToDashboard(String message) { //USE HTTP PROTOCOL

    }

    @Override
    public void sendMessageToSensor(String message) { //use MQTT PROTOCOL

    }

    @Override
    public void receiveDataFromSensor() { //USE MQTT PROTOCOL ()

    }

    @Override
    public void receiveDataFromArduino() { //USE SERIAL PROTOCOL

    }

    @Override
    public void run() {
        try {
            this.startController();
        } catch (Exception ex) {
            System.out.println("Error in starting CHANNEL CONTROLLER MANAGER");
        }
    }
}
