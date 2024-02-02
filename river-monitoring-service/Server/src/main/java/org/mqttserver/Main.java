package org.mqttserver;


import org.mqttserver.policy.ChannelControllerManager;
import org.mqttserver.policy.ChannelControllerManagerImpl;
import org.mqttserver.policy.SystemController;
import org.mqttserver.policy.SystemControllerImpl;
import org.mqttserver.presentation.Status;
import org.mqttserver.serial.SerialCommChannel;
import org.mqttserver.serial.SerialCommChannelImpl;
import org.mqttserver.serial.SerialScanner;
import org.mqttserver.serial.SerialScannerImpl;
import org.mqttserver.services.MQTT.Broker;
import org.mqttserver.services.MQTT.BrokerImpl;

public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Welcome in Smart River Monitoring Server...");

        //start the broker (MQTTServer)
        Broker broker = new BrokerImpl();
        broker.initialize(broker.getMqttServer());

        //Init Controller Manager
        ChannelControllerManager channelControllerManager = new ChannelControllerManagerImpl(broker, null);

        //////////////////
        //attesa necessaria per fare in modo che Arduino completi il reboot
        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        System.out.println("Ready.");
        while (true){
            System.out.println("Server send message...");
            channelControllerManager.sendMessageToArduino(broker.getSystemController().getStatus()); //this message must be different
            String msg = channelControllerManager.receiveDataFromArduino();
            System.out.println("Received from arduino: "+ msg);
            Thread.sleep(1000);

         }

        ///////////////////////////////////////////////////////////

        //TODO: start the HTTPServer to communicate with Client-Dashboard passing values of system
        //HttpServer httpServer = new HttpServer() .....



        
    }
}