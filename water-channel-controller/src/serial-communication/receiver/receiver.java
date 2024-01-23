import jssc.*;

public class receiver {
    public static void main(String[] args) {
        SerialPort serialPort = new SerialPort("/dev/ttyUSB0");
        try {
            serialPort.openPort();
            serialPort.setParams(9600, 8, 1, 0);
            serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
                    SerialPort.FLOWCONTROL_RTSCTS_OUT);
            serialPort.addEventListener((SerialPortEventListener) new PortReader(), SerialPort.MASK_RXCHAR);
        } catch (SerialPortException ex) {
            System.out.println(ex);
        }
    }
}