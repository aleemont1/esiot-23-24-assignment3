package org.mqttserver;


import io.vertx.core.Vertx;
import org.mqttserver.policy.ChannelControllerManager;
import org.mqttserver.policy.ChannelControllerManagerImpl;
import org.mqttserver.presentation.Status;
import org.mqttserver.services.HTTP.DataService;
import org.mqttserver.services.MQTT.Broker;
import org.mqttserver.services.MQTT.BrokerImpl;


public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Welcome in Smart River Monitoring Server...");
        //start the broker (MQTTServer)
        Broker broker = new BrokerImpl();
        broker.initialize(broker.getMqttServer());

        //start the httpServer and DataService (for dashboard and http server)
        Vertx vertx = Vertx.vertx();
        DataService service = new DataService(8050, broker);
        vertx.deployVerticle(service);

        //Init Channel Controller Manager
        ChannelControllerManager channelControllerManager = new ChannelControllerManagerImpl(broker);

        while (true) {
            if (!broker.getSystemController().getIsManual()) {
                channelControllerManager.sendMessageToArduino(Status.ALARM_TOO_HIGH); //I send the message to arduino with state
                String msg = channelControllerManager.receiveDataFromArduino(); //I receive the answer from arduino
                broker.getSystemController().checkValveValue(msg, broker); //check valve value
            } else {
                channelControllerManager.sendMessageToArduino(broker.getSystemController().getValveValue()); //I send the message to arduino with state
            }
            Thread.sleep(400);
        }
    }
}