package org.mqttserver.policy;

import org.mqttserver.presentation.*;
import org.mqttserver.serial.SerialCommChannel;
import org.mqttserver.serial.SerialCommChannelImpl;
import org.mqttserver.serial.SerialScanner;
import org.mqttserver.serial.SerialScannerImpl;
import org.mqttserver.services.HTTP.HTTPServer;
import org.mqttserver.services.MQTT.Broker;

public class ChannelControllerManagerImpl implements ChannelControllerManager {

    private Broker broker;

    private HTTPServer httpServer;

    private SerialCommChannel serialCommChannel;
    private SerialScanner serialScanner = new SerialScannerImpl();



    public ChannelControllerManagerImpl(Broker broker, HTTPServer httpServer) throws Exception {
        //Init broker and http server
        this.broker = broker;
        this.httpServer = httpServer;

        //init serial communication
        this.serialCommChannel = new SerialCommChannelImpl(this.serialScanner.getConnectedPort(), 9600 );
        System.out.println("Started CHANNEL CONTROLLER " + "\nChannel Controller Controls MQTTServer: " +
               this.broker.getMqttServer().toString() + " ON PORT: "  + this.broker.getMqttServer().actualPort());

    }


    @Override
    public void sendMessageToArduino(Status status) {
        MessageToArduino messageToArduino = new MessageToArduino(status);
        this.serialCommChannel.sendMessageToArduino(JSONUtils.objectToJson(messageToArduino));



    }

    @Override
    public String receiveDataFromArduino() throws InterruptedException { //USE SERIAL PROTOCOL
        return this.serialCommChannel.receiveMessageFromArduino();
    }

    @Override
    public void sendMessageToDashboard(MessageToDashboard message) { //USE HTTP PROTOCOL

    }

    @Override
    public void sendMessageToSensor(MessageToSensor message) { //use MQTT PROTOCOL

    }

    @Override
    public void receiveDataFromSensor() { //USE MQTT PROTOCOL ()

    }


}
