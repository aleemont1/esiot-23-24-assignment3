package org.mqttserver.policy;

import io.vertx.core.eventbus.Message;
import org.mqttserver.presentation.MessageToArduino;
import org.mqttserver.presentation.MessageToDashboard;
import org.mqttserver.presentation.MessageToSensor;
import org.mqttserver.presentation.Status;

public interface ChannelControllerManager {

    //ARDUINO
    void sendMessageToArduino(Status status);

    void sendMessageToArduino(int valveValue);

    String receiveDataFromArduino() throws InterruptedException;

}
