package org.mqttserver.services.MQTT;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.Vertx;
import io.vertx.mqtt.MqttEndpoint;
import io.vertx.mqtt.MqttServer;
import io.vertx.mqtt.MqttServerOptions;

import java.util.ArrayList;
import java.util.List;



// topic della frequenza: sensor/freq,  {"freq":""}   ,  sensor/wl   {"WL":""}

public class BrokerImpl implements Broker {

    private final String HOST = "broker";
    private final int SERVER_PORT = 1883;

    protected MqttServer mqttServer = null;

    protected MqttServerOptions mqttServerOptions = null;

    private final Vertx vertx;

    private final List<MqttEndpoint> subscribedClients = new ArrayList<>();


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

    @Override
    public MqttServer getMqttServer() {
        return this.mqttServer;
    }

}
