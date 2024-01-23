package org.mqttserver;


import org.mqttserver.policy.ChannelControllerManager;
import org.mqttserver.policy.ChannelControllerManagerImpl;
import org.mqttserver.serial.ReaderImpl;
import org.mqttserver.serial.Writer;
import org.mqttserver.serial.WriterImpl;
import org.mqttserver.services.MQTT.Broker;
import org.mqttserver.services.MQTT.BrokerImpl;

import java.io.UnsupportedEncodingException;

public class Main {
    public static void main(String[] args) {
        System.out.println("Welcome in Smart River Monitoring Server...");

        //start the broker (MQTTServer)
        Broker broker = new BrokerImpl();
        broker.initialize(broker.getMqttServer());

        //start the server (HTTP)


        //start the controller manager

        ChannelControllerManager channelControllerManager = new ChannelControllerManagerImpl(broker, null);
        channelControllerManager.run();

        //Writer writer = new WriterImpl();
        //writer.writeDataOnSerial("This is a message wrote on serial line by writer");

        //start the Serial Reader
        //ReaderImpl readerImpl = new ReaderImpl();
        //readerImpl.run();


        //start the writer on serial Line

        //TODO: start the HTTPServer to communicate with Client-Dashboard passing values of system
        //HttpServer httpServer = new HttpServer() .....



    }
}