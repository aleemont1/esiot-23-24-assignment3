package org.mqttserver;


import com.google.gson.stream.MalformedJsonException;
import org.mqttserver.policy.ChannelControllerManager;
import org.mqttserver.policy.ChannelControllerManagerImpl;
import org.mqttserver.policy.SystemController;
import org.mqttserver.policy.SystemControllerImpl;
import org.mqttserver.presentation.JSONUtils;
import org.mqttserver.presentation.MessageFromArduino;
import org.mqttserver.presentation.Status;
import org.mqttserver.serial.SerialCommChannel;
import org.mqttserver.serial.SerialCommChannelImpl;
import org.mqttserver.serial.SerialScanner;
import org.mqttserver.serial.SerialScannerImpl;
import org.mqttserver.services.MQTT.Broker;
import org.mqttserver.services.MQTT.BrokerImpl;

import java.nio.charset.MalformedInputException;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Welcome in Smart River Monitoring Server...");

        //start the broker (MQTTServer)
        Broker broker = new BrokerImpl();
        broker.initialize(broker.getMqttServer());

        //Init Controller Manager
        ChannelControllerManager channelControllerManager = new ChannelControllerManagerImpl(broker, null);

        //////////////////


        while (true){
            channelControllerManager.sendMessageToArduino(broker.getSystemController().getStatus()); //this message must be different
            String msg = channelControllerManager.receiveDataFromArduino();
            System.out.println("Received: " + msg);

            //da qui fino al segnalino da mettere nel system controller
            try {
                Integer valveValue = JSONUtils.jsonToObject(msg,MessageFromArduino.class).getValveValue();
                if (valveValue.equals(broker.getSystemController().getStatusValveValue().get(broker.getSystemController().getStatus()))) {
                    System.out.println("SERVER: VALVOLA OK");
                } else {
                    System.err.println("SERVER: VALVOLA NON COERENTE CON LO STATO DEL SISTEMA!");
                }
            } catch (Exception ex) {
                System.err.println("Il server è In attesa di dati validi da parte di Arduino....");
            }


            Thread.sleep(500);
         }

        ///////////////////////////////////////////////////////////

        //TODO: start the HTTPServer to communicate with Client-Dashboard passing values of system
        //HttpServer httpServer = new HttpServer() .....



        
    }
}