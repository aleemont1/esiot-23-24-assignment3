package org.mqttserver.policy;

public interface ChannelControllerManager {


    //ARDUINO
    void sendMessageToArduino();
    String receiveDataFromArduino() throws InterruptedException;


    //ESP32

    void sendMessageToSensor(String message);

    void receiveDataFromSensor();


    //DASHBOARD

    void sendMessageToDashboard(String message);







}
