package org.mqttserver.policy;

import org.mqttserver.presentation.MessageToArduino;
import org.mqttserver.presentation.MessageToDashboard;
import org.mqttserver.presentation.MessageToSensor;

public interface ChannelControllerManager extends Runnable {


    void sendMessageToArduino(String message);

    void sendMessageToDashboard(String message);

    void sendMessageToSensor(String message);

    void receiveDataFromSensor();

    void receiveDataFromArduino();

    boolean receivedEndOfMessage(); //valid for serial line

    boolean sendEndOfMessage(); //valid for serial line




}
