package org.mqttserver;

import org.mqttserver.service.Broker;
import org.mqttserver.service.BrokerImpl;

public class Main {


    public static void main(String[] args) {

        System.out.println("Welcome in Smart River Monitoring Server");

        Broker broker = new BrokerImpl();


    }
}