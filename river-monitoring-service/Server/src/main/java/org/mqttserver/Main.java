package org.mqttserver;


import com.google.gson.stream.MalformedJsonException;
import org.mqttserver.policy.ChannelControllerManager;
import org.mqttserver.policy.ChannelControllerManagerImpl;
import org.mqttserver.presentation.JSONUtils;
import org.mqttserver.presentation.MessageFromArduino;
import org.mqttserver.services.MQTT.Broker;
import org.mqttserver.services.MQTT.BrokerImpl;


public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Welcome in Smart River Monitoring Server...");
        //start the broker (MQTTServer)
        Broker broker = new BrokerImpl();
        broker.initialize(broker.getMqttServer());
        //Init Channel Controller Manager
        ChannelControllerManager channelControllerManager = new ChannelControllerManagerImpl(broker, null);

         while (true){
            channelControllerManager.sendMessageToArduino(broker.getSystemController().getStatus()); //I send the message to arduino with state
            String msg = channelControllerManager.receiveDataFromArduino(); //i receive the answer from arduino
            broker.getSystemController().checkValveValue(msg, broker); //check valve value
            Thread.sleep(200);
         }
    }
}