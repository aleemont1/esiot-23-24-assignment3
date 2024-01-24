package org.mqttserver.services.MQTT;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttServer;
import io.vertx.mqtt.MqttServerOptions;
import io.vertx.mqtt.MqttTopicSubscription;
import org.mqttserver.services.MQTT.publisher.MQTTPublisherImpl;
import org.mqttserver.services.MQTT.subscriber.MQTTSubscriberImpl;

import java.util.ArrayList;
import java.util.List;

/*
*   THIS CLASS IS JUST TO TRY PUBLISH AND SUBSCRIBE, THE CODE MUST BE DIVIDED INTO THE RELATED CORRECT CLASS
*
* */
public class BrokerImpl implements Broker {

    private final String HOST = "localhost";
    private final int SERVER_PORT = 1883;

    protected MqttServer mqttServer = null;

    protected MqttServerOptions mqttServerOptions = null;

    private MQTTPublisherImpl mqttPublisher = null; //the object responsable of publishing the message on a certain topic (response)
    private MQTTSubscriberImpl mqttSubscriber = null; //the object rensposable of subscribing a topic from the client (request)


    public BrokerImpl() {
        //Setting up Vertx, Server Options and Server
        Vertx vertx = Vertx.vertx();
        this.mqttServerOptions = this.createMqttServerOptions();
        this.mqttServer = this.createMqttServer(vertx, mqttServerOptions);
    }

    private MqttServerOptions createMqttServerOptions() {
        return new MqttServerOptions()
                .setPort(SERVER_PORT)
                .setHost(HOST);
    }

    private MqttServer createMqttServer(Vertx vertx, MqttServerOptions mqttServerOptions) {
        return MqttServer.create(vertx, mqttServerOptions);
    }

    @Override
    public void initialize(MqttServer mqttServer) {
        mqttServer.endpointHandler(endpoint -> {

            // shows main connect info
            System.out.println("MQTT client [" + endpoint.clientIdentifier() + "] request to connect, clean session = " + endpoint.isCleanSession());

            if (endpoint.auth() != null) {
                System.out.println("[username = " + endpoint.auth().getUsername() + ", password = " + endpoint.auth().getPassword() + "]");
            }
            if (endpoint.will() != null) {
                System.out.println("[will flag = " + endpoint.will().isWillFlag() + " topic = " + endpoint.will().getWillTopic() + " msg = " + endpoint.will().getWillMessage() +
                        " QoS = " + endpoint.will().getWillQos() + " isRetain = " + endpoint.will().isWillRetain() + "]");
            }

            System.out.println("[keep alive timeout = " + endpoint.keepAliveTimeSeconds() + "]");

            // accept connection from the remote client
            endpoint.accept(false);

            // handling requests for subscriptions (get info from the server)
            endpoint.subscribeHandler(subscribe -> {
                List<MqttQoS> grantedQosLevels = new ArrayList<>();
                for (MqttTopicSubscription s : subscribe.topicSubscriptions()) {
                    System.out.println("Subscription for " + s.topicName() + " with QoS " + s.qualityOfService());
                    grantedQosLevels.add(s.qualityOfService());
                }
                // ack the subscriptions request
                endpoint.subscribeAcknowledge(subscribe.messageId(), grantedQosLevels);

                // just as example, publish a message on the first topic with requested QoS
                endpoint.publish(subscribe.topicSubscriptions().get(0).topicName(),
                        Buffer.buffer("Hello from the Vert.x MQTT server"),
                        subscribe.topicSubscriptions().get(0).qualityOfService(),
                        false,
                        false);

                // specifing handlers for handling QoS 1 and 2
                endpoint.publishAcknowledgeHandler(messageId -> {

                    System.out.println("Received ack for message = " + messageId);

                }).publishReceivedHandler(endpoint::publishRelease).publishCompletionHandler(messageId -> {

                    System.out.println("Received ack for message = " + messageId);
                });
            });

            // handling requests for unsubscriptions
            endpoint.unsubscribeHandler(unsubscribe -> {

                for (String t : unsubscribe.topics()) {
                    System.out.println("Unsubscription for " + t);
                }
                // ack the subscriptions request
                endpoint.unsubscribeAcknowledge(unsubscribe.messageId());
            });

            // handling ping from client
            endpoint.pingHandler(v -> {
                System.out.println("Ping received from client");
            });

            // handling disconnect message
            endpoint.disconnectHandler(v -> {
                System.out.println("Received disconnect from client");
            });

            // handling closing connection
            endpoint.closeHandler(v -> {
                System.out.println("Connection closed");
            });

            // handling incoming published messages
            endpoint.publishHandler(message -> {

                System.out.println("Just received message on [" + message.topicName() + "] payload [" + message.payload() + "] with QoS [" + message.qosLevel() + "]");

                if (message.qosLevel() == MqttQoS.AT_LEAST_ONCE) {
                    endpoint.publishAcknowledge(message.messageId());
                } else if (message.qosLevel() == MqttQoS.EXACTLY_ONCE) {
                    endpoint.publishReceived(message.messageId());
                }

            }).publishReleaseHandler(endpoint::publishComplete);
        })
        .listen(SERVER_PORT, HOST, ar -> {
            if (ar.succeeded()) {
                System.out.println("MQTT server is listening on port " + mqttServer.actualPort());

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
