package org.mqttserver.presentation;

public class EndOfMessage {


    private final String EOM = "END"; //THE STRING RECOGNIZED AS EOM

    public EndOfMessage() {
        //empty constructor
    }

    public String getEOM() {
        return this.EOM;
    }

}
