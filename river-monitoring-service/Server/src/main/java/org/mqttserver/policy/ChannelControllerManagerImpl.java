package org.mqttserver.policy;

import io.vertx.mqtt.MqttServer;
import org.mqttserver.presentation.EndOfMessage;
import org.mqttserver.serial.SerialReader;
import org.mqttserver.serial.SerialReaderImpl;
import org.mqttserver.serial.SerialWriter;
import org.mqttserver.serial.SerialWriterImpl;
import org.mqttserver.services.HTTP.HTTPServer;
import org.mqttserver.services.MQTT.Broker;
import org.mqttserver.services.MQTT.BrokerImpl;

import java.util.logging.Handler;

public class ChannelControllerManagerImpl implements ChannelControllerManager {

    private Broker broker;
    private HTTPServer httpServer = null;

    private SerialWriter serialWriter = null;

    private SerialReaderImpl serialReader = null;



    public ChannelControllerManagerImpl(Broker broker, HTTPServer httpServer) {
        this.broker = broker;
        this.httpServer = httpServer;
        this.serialWriter = new SerialWriterImpl();
        this.serialReader = new SerialReaderImpl();
    }

    private void startController() {
        //TODO: here the implementation of starting
        System.out.println("Started CHANNEL CONTROLLER " + "\nChannel Controller Control MQTTServer: " +
                this.broker.getMqttServer().toString() + " ON PORT: "  + this.broker.getMqttServer().actualPort());
    }

    @Override
    public void sendMessageToArduino(String message) { //USE SERIAL LINE

        //TODO: at the end i always emd the message with EOM
        sendEndOfMessage();


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
    public boolean receivedEndOfMessage() { //valid for serial

        //TODO: when receive end of message it means i can take control of the serial line
        return false;
    }

    @Override
    public boolean sendEndOfMessage() { //valid for serial

        //TODO: when i call this method it means i have finished to send my message on serial line so i send another message that represent the EOF
        EndOfMessage endOfMessage = new EndOfMessage();

        this.serialWriter.writeDataOnSerial(endOfMessage.getEOM());
        return true;
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
