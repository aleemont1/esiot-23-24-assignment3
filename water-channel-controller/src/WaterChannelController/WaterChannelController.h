#ifndef __WATERCHANNELCONTROLLER_H__
#define __WATERCHANNELCONTROLLER_H__

#include "../serial_communication/Client-Arduino/ValveController.h"
#include "../serial_communication/Client-Arduino/JsonProcessor.h"
#include "LiquidCrystal_I2C.h"
#include "Servo.h"
#include "WaterChannelController/State.h"
#include "../serial_communication/Client-Arduino/MessageReceiver.h"
#include "Arduino.h"

/**
 * @class WaterChannelController
 * @brief This class is responsible for controlling a water channel.
 *
 * The WaterChannelController class provides functionality to control a water channel using a servo motor,
 * a button for manual control, and a potentiometer for adjusting the valve opening level. It also includes
 * an LCD display to show the current status of the system.
 */
class WaterChannelController
{
public:
    /**
     * @brief Construct a new Water Channel Controller object.
     *
     * @param servoPin The pin number where the servo motor is connected.
     * @param buttonPin The pin number where the button for manual control is connected.
     * @param potentiometerPin The pin number where the potentiometer for adjusting the valve opening level is connected.
     * @param lcdAddr The I2C address of the LCD.
     * @param lcdColumns The number of columns in the LCD.
     * @param lcdRows The number of rows in the LCD.
     */
    WaterChannelController(int servoPin, int buttonPin, int potentiometerPin, int lcdAddr, int lcdColumns, int lcdRows);

    /**
     * @brief Destroy the Water Channel Controller object
     *
     */
    ~WaterChannelController();

    /**
     * @brief Initializes the Water Channel Controller.
     *
     * This method sets up the necessary hardware interfaces for the water channel controller.
     * It sets the mode of the button pin to INPUT, attaches the servo to its pin, and initializes
     * the LCD display with the specified dimensions. It also sets the initial position of the servo
     * to represent a fully closed valve and updates the LCD display with the initial status.
     */
    void initialize();

    /**
     * @brief Initializes the button used to control the water channel manually.
     * This method sets the mode of the button pin to INPUT, which allows the button to be used for manual control.
     */
    void initializeButton();

    /**
     * @brief Initializes the servo motor used to control the position of the water valve.
     * This method attaches the servo to the specified pin, which allows the servo to be controlled by the Arduino.
     */
    void initializeServo();

    /**
     * @brief Initializes the valve to a default position (fully closed).
     * This method sets the initial position of the servo to represent a fully closed valve.
     */
    void initializeValve();

    /**
     * @brief Initializes the LCD display.
     * This method initializes the LCD display with the specified dimensions and prints the initial message.
     */
    void initializeLcd();

    void parseValveValue();

    /**
     * @brief Updates the position of the valve based on the specified opening level.
     *
     * This method adjusts the position of the servo motor, which in turn changes the opening level of the valve.
     * The valve opening level is a percentage, where 0% represents a fully closed valve and 100% represents a fully open valve.
     * The method maps the valve opening level to a servo angle (0-180 degrees) and then updates the servo position.
     * If the provided valve opening level is outside the valid range (0-100), the method does nothing.
     *
     * @param valveOpeningLevel The desired level to which the valve should be opened, expressed as a percentage (0-100).
     */
    void updateValvePosition(int valveOpeningLevel);

    /**
     * @brief Checks the status of the button for manual control.
     *
     * This method reads the state of the button connected to the buttonPin. If the button is pressed,
     * it toggles the manualMode flag, which enables or disables manual control of the water channel.
     * The method also debounces the button input to prevent false triggering.
     */
    void checkButtonStatus();

    /**
     * @brief Toggles the operating mode of the water channel controller between manual and automatic.
     */
    void toggleState();

    /**
     * @brief Enables manual control of the water channel.
     *
     * This method is used to manually control the opening level of the valve. When manual control mode is active,
     * it reads the value from the potentiometer connected to the potentiometerPin, maps this value to a valve opening level,
     * and then updates the valve position accordingly. The current valve opening level is also displayed on the LCD.
     */
    void manualControl();

    /**
     * @brief Updates the LCD display with the current status of the system.
     *
     * This method refreshes the LCD display to show the current status of the water channel controller.
     * It displays the current valve opening level (as a percentage) and the current operating mode (manual or automatic).
     * The valve opening level is displayed on the first row of the LCD, and the operating mode is displayed on the second row.
     */
    void updateLCD();

    /**
     * @brief Converts the valve opening level to a servo angle.
     *
     * This method maps the valve opening level (0-100) to a servo angle (0-180).
     * A valve opening level of 0 corresponds to a servo angle of 0 (valve fully closed),
     * and a valve opening level of 100 corresponds to a servo angle of 180 (valve fully open).
     *
     * @param valveOpeningLevel The level to which the valve should be opened (0-100).
     * @return int The corresponding servo angle (0-180).
     */
    int mapValveOpeningLevelToServoAngle(int valveOpeningLevel);

    /**
     * @brief Reads the status of the water channel controller.
     * Checks the button status and performs manual control if the controller is in manual mode.
     */
    void reading();

private:
    int servoPin;                                    ///< The pin number to which the servo motor is connected.
    int address = 0;                                 ///< The I2C address of the LCD display.
    int columns = 16;                                ///< The number of columns in the LCD display.
    int rows = 2;                                    ///< The number of rows in the LCD display.
    Servo valveServo;                                ///< The servo motor that controls the position of the water valve.
    int buttonPin;                                   ///< The pin number to which the manual control button is connected.
    int potentiometerPin;                            ///< The pin number to which the potentiometer for adjusting the valve opening level is connected.
    bool manualMode;                                 ///< A flag indicating whether the system is in manual control mode.
    LiquidCrystal_I2C lcd;                           ///< The object representing the LCD display.
    int currentValveOpeningLevel;                    ///< The current level (0-100) to which the water valve is opened.
    const int MIN_VALVE_OPENING_LEVEL = 0;           ///< The minimum valid valve opening level.
    const int MAX_VALVE_OPENING_LEVEL = 100;         ///< The maximum valid valve opening level.
    const int MIN_SERVO_ANGLE = 0;                   ///< The minimum angle to which the servo can rotate.
    const int MAX_SERVO_ANGLE = 180;                 ///< The maximum angle to which the servo can rotate.
    const int MIN_POTENTIOMETER_VALUE = 0;           ///< The minimum reading from the potentiometer.
    const int MAX_POTENTIOMETER_VALUE = 1023;        ///< The maximum reading from the potentiometer.
    ValveController valveController;                 ///< The valve controller object used to set the valve value based on the system state.
    JsonProcessor jsonProcessor;                     ///< The JSON processor object used to parse the JSON data received from the server.
    State state;                                     ///< The state object used to store the current state of the system.
    const unsigned long DEBOUNCE_DELAY = 200;        ///< The delay (in milliseconds) used to debounce the button input.
    MessageReceiver messageReceiver;                 ///< The message receiver object used to receive messages from the server.
    const unsigned long SERVO_UPDATE_INTERVAL = 500; ///< The interval (in milliseconds) between servo position updates.
};

#endif // __WATERCHANNELCONTROLLER_H__