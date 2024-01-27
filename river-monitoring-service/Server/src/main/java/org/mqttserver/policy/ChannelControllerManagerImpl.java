package org.mqttserver.policy;

import org.mqttserver.presentation.EndOfMessage;
import org.mqttserver.serial.SerialCommChannel;
import org.mqttserver.serial.SerialCommChannelImpl;
import org.mqttserver.serial.SerialScanner;
import org.mqttserver.serial.SerialScannerImpl;
import org.mqttserver.services.HTTP.HTTPServer;
import org.mqttserver.services.MQTT.Broker;

public class ChannelControllerManagerImpl implements ChannelControllerManager {

    private Broker broker;
    private HTTPServer httpServer = null;

    private SerialCommChannel serialCommChannel;
    private SerialScanner serialScanner = new SerialScannerImpl();

    public ChannelControllerManagerImpl(Broker broker, HTTPServer httpServer) throws Exception {
        //Init broker and http server
        this.broker = broker;
        this.httpServer = httpServer;

        //init serial communication
        this.serialCommChannel = new SerialCommChannelImpl(this.serialScanner.getConnectedPort(), 9600 );


    }

    private void startController() {
        //TODO: here the implementation of starting
        System.out.println("Started CHANNEL CONTROLLER " + "\nChannel Controller Control MQTTServer: " +
                this.broker.getMqttServer().toString() + " ON PORT: "  + this.broker.getMqttServer().actualPort());
    }

    @Override
    public void sendMessageToArduino(String message) { //USE SERIAL LINE


       /* MessageToArduino messageToArduino = new MessageToArduino();
        messageToArduino.setStatus(this);*/

        this.serialCommChannel.sendMessageToArduino(message);

        //TODO: at the end i always emd the message with EOM
        sendEndOfMessage();


    }

    @Override
    public String receiveDataFromArduino() throws InterruptedException { //USE SERIAL PROTOCOL
        return this.serialCommChannel.receiveMessageFromArduino();
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
    public boolean receivedEndOfMessage() { //valid for serial

        //TODO: when receive end of message it means i can take control of the serial line
        return false;
    }

    @Override
    public boolean sendEndOfMessage() { //valid for serial

        //TODO: when i call this method it means i have finished to send my message on serial line so i send another message that represent the EOF
        EndOfMessage endOfMessage = new EndOfMessage();

       // this.serialWriter.writeDataOnSerial(endOfMessage.getEOM());
        return true;
    }

}
