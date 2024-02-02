package org.mqttserver.services.MQTT;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttEndpoint;
import io.vertx.mqtt.MqttServer;
import io.vertx.mqtt.MqttServerOptions;
import org.mqttserver.policy.ChannelControllerManager;
import org.mqttserver.policy.ChannelControllerManagerImpl;
import org.mqttserver.policy.SystemController;
import org.mqttserver.policy.SystemControllerImpl;
import org.mqttserver.presentation.JSONUtils;
import org.mqttserver.presentation.MessageFromSensor;
import org.mqttserver.presentation.MessageToArduino;
import org.mqttserver.presentation.MessageToSensor;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;


// topic della frequenza: sensor/freq,  {"freq":""}   ,  sensor/wl   {"WL":""}

public class BrokerImpl implements Broker {

    private final String HOST = "broker";
    private final int SERVER_PORT = 1883;

    protected MqttServer mqttServer = null;

    protected MqttServerOptions mqttServerOptions = null;

    private final Vertx vertx;

    private final List<MqttEndpoint> subscribedClients = new ArrayList<>();

    private SystemController systemController = new SystemControllerImpl();

    public BrokerImpl() {
        //Setting up Vertx, Server Options and Server
        this.vertx = Vertx.vertx();
        this.mqttServerOptions = this.createMqttServerOptions();
        this.mqttServer = this.createMqttServer(vertx);
    }

    private MqttServerOptions createMqttServerOptions() {
        return new MqttServerOptions()
                .setPort(SERVER_PORT)
                .setHost(HOST);
    }

    private MqttServer createMqttServer(Vertx vertx) {
        return MqttServer.create(vertx);
    }

    @Override
    public void initialize(MqttServer mqttServer) {


        mqttServer.endpointHandler(endpoint -> {
            // Handle connection
            System.out.println("Client connected: " + endpoint.clientIdentifier());

            // Handle subscription
            endpoint.subscribeHandler(subscribe -> {
                subscribe.topicSubscriptions().forEach(topic -> {
                    System.out.println("Client subscribed to: " + topic.topicName());
                    subscribedClients.add(endpoint);

                });
            });


            endpoint.publishHandler(message -> {
                System.out.println("Received message on topic " + message.topicName() + " with payload: " + message.payload().toString());
                if (!subscribedClients.isEmpty()) {
                    for (MqttEndpoint client : subscribedClients) {
                        client.publish(message.topicName(), message.payload(), MqttQoS.valueOf(0), false, false);
                    }
                }

                if (Objects.equals(message.topicName(), "/sensor/wl")) {
                    //setta lo stato del sistema in base al valore rilevato dell acqua
                    MessageFromSensor messageObj  = new MessageFromSensor(JSONUtils.jsonToObject(message.payload().toString(), MessageFromSensor.class).getWL());
                    System.out.println("Value received from ESP32: " + messageObj.getWL());
                    this.updateSystem(messageObj.getWL());

                    //pubblicare la frequenza su tutti i client
                    MessageToSensor messageToSensor = new MessageToSensor(this.systemController.getFrequency());
                    System.out.println("MESSAGE TO SENSOR: " + JSONUtils.objectToJson(messageToSensor));

                    for (MqttEndpoint client : subscribedClients) {

                        client.publish("sensor/freq", Buffer.buffer(JSONUtils.objectToJson(messageToSensor)), MqttQoS.valueOf(0), false, false);
                    }

                }

            });

            endpoint.disconnectHandler(disconnect -> System.out.println("Client disconnected"));

           endpoint.closeHandler(handler -> {
               System.out.println("Client close the connection: " + endpoint.clientIdentifier());
               subscribedClients.remove(endpoint);

               System.out.println("Subscriber " + endpoint + "removed from list. ACTUAL LIST: " + subscribedClients);
           });

            // Acknowledge the connection request
            endpoint.accept(false);
        });

        mqttServer.listen( ar -> {
            if (ar.succeeded()) {
                System.out.println("MQTT server is listening on port " + ar.result().actualPort() + " " + ar);
            } else {
                System.err.println("Error on starting the server" + ar.cause().getMessage());
            }
        });

    }

    private void updateSystem(float WL) {
        this.systemController.setWL(WL);
        //manda un messaggio ad esp con la frequenza in base allo satto settata del sistema

    }


    @Override
    public MqttServer getMqttServer() {
        return this.mqttServer;
    }

    @Override
    public SystemController getSystemController() {
        return this.systemController;
    }

}
