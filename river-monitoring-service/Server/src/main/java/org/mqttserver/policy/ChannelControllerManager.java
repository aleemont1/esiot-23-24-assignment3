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



    //this two methods are not useful in this implementation
    boolean receivedEndOfMessage(); //valid for serial line

    boolean sendEndOfMessage(); //valid for serial line




}
