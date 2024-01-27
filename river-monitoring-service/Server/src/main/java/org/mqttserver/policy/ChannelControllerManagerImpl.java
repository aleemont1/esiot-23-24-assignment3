package org.mqttserver.policy;

import com.google.gson.Gson;
import org.mqttserver.presentation.EndOfMessage;
import org.mqttserver.presentation.JSONUtils;
import org.mqttserver.presentation.MessageToArduino;
import org.mqttserver.presentation.Status;
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
    public void sendMessageToArduino() { //USE SERIAL LINE

        Status actualStatus;

        this.broker.getMqttServer();







        MessageToArduino messageToArduino = new MessageToArduino(Status.NORMAL); //just for testing i add always NORMAL

        this.serialCommChannel.sendMessageToArduino(JSONUtils.objectToJson(messageToArduino));

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
