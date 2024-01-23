// import java.io.BufferedReader;
// import java.io.IOException;
// import java.io.InputStreamReader;
// import java.io.OutputStream;
// import java.lang.Object;

// /***
// * This class implements a serial client that connects to a serial server
// * through a serial port.
// * It receives messages from the server and sends confirmation messages to the
// * server.
// */
// public class SerialClient {

// public static void main(String[] args) {
// try {
// // TODO: change this value to the correct port name
// String portName = "COM1";
// // TODO: change this value to the correct baud rate
// int baudRate = 9600;

// // Open the serial port connection
// CommPortIdentifier portIdentifier =
// CommPortIdentifier.getPortIdentifier(portName);
// // Select the serial port and establish a connection with it (timeout: 2s)
// SerialPort serialPort = (SerialPort) portIdentifier.open("SerialClient",
// 2000);

// // Set the parameters of the connection
// serialPort.setSerialPortParams(baudRate, SerialPort.DATABITS_8,
// SerialPort.STOPBITS_1,
// SerialPort.PARITY_NONE);

// // Stream of input and output data to/from the serial port
// BufferedReader input = new BufferedReader(new
// InputStreamReader(serialPort.getInputStream()));
// OutputStream output = serialPort.getOutputStream();

// // Phase 1 - Receive messages from the server
// String receivedMessage;
// while (!(receivedMessage = input.readLine()).equals("END")) {
// // Processa il messaggio ricevuto dal server
// processReceivedMessage(receivedMessage);
// }

// // Phase 2 - Send confirmation messages to the server
// String confirmationMessage1 = "valveValue:25";
// String confirmationMessage2 = "status:NORMAL";

// output.write((confirmationMessage1 + "\n").getBytes());
// output.write((confirmationMessage2 + "\n").getBytes());
// output.write("END\n".getBytes());

// // Close the serial port connection
// serialPort.close();
// } catch (Exception e) {
// e.printStackTrace();
// }
// }

// /***
// * This method implements the logic to process the received message from the
// * server. It prints the received message to the console.
// *
// * @param message
// */
// private static void processReceivedMessage(String message) {
// // TODO: Implements the logic to process the received message from the server
// // here
// System.out.println("Received message from server: " + message);
// }
// }
