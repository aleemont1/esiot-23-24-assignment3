#include "WaterChannelController.h"

WaterChannelController::WaterChannelController(int servoPin, int buttonPin, int potentiometerPin, int lcdAddr, int lcdColumns, int lcdRows)
    : servoPin(servoPin), buttonPin(buttonPin), potentiometerPin(potentiometerPin), manualMode(false), lcd(lcdAddr, lcdColumns, lcdRows), currentValveOpeningLevel(0)
{
    initialize();
}

WaterChannelController::~WaterChannelController()
{
    valveServo.detach();
}

void WaterChannelController::initialize()
{
    initializeServo();
    initializeButton();
    initializeValve();
    // initializeLcd(); // TODO: Uncomment this line after solving the issue with the LCD
    updateLCD();
}

void WaterChannelController::initializeServo()
{
    valveServo.attach(servoPin);
}

void WaterChannelController::initializeButton()
{
    pinMode(buttonPin, INPUT);
}

void WaterChannelController::initializeValve()
{
    valveServo.write(MIN_SERVO_ANGLE);
}

void WaterChannelController::initializeLcd()
{
    lcd.begin(columns, rows);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Water Channel");
}

void WaterChannelController::updateValvePosition(int valveOpeningLevel)
{
    static unsigned long lastUpdate = 0;
    unsigned long now = millis();

    // Only update the servo position if enough time has passed since the last update
    if (now - lastUpdate >= SERVO_UPDATE_INTERVAL)
    {
        int servoAngle = mapValveOpeningLevelToServoAngle(valveOpeningLevel);
        valveServo.write(servoAngle);
        currentValveOpeningLevel = valveOpeningLevel;
        updateLCD();

        // Update the time of the last update
        lastUpdate = now;
    }
}

int WaterChannelController::mapValveOpeningLevelToServoAngle(int valveOpeningLevel)
{
    return map(valveOpeningLevel, MIN_VALVE_OPENING_LEVEL, MAX_VALVE_OPENING_LEVEL, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
}

void WaterChannelController::updateLCD()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Valve: ");
    lcd.print(currentValveOpeningLevel);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Mode: ");
    lcd.print(state == State::MANUAL ? "MANUAL" : "AUTOMATIC");
}

void WaterChannelController::manualControl()
{
    int potentiometerValue = analogRead(potentiometerPin);
    int valveOpeningLevel = map(potentiometerValue, MIN_POTENTIOMETER_VALUE, MAX_POTENTIOMETER_VALUE, MIN_VALVE_OPENING_LEVEL, MAX_VALVE_OPENING_LEVEL);
    updateValvePosition(valveOpeningLevel);
}

void WaterChannelController::reading()
{
    checkButtonStatus();

    switch (state)
    {
    case State::MANUAL:
        manualControl();
        break;

    case State::AUTOMATIC:
        String receivedContent = messageReceiver.getReceivedContent();
        String systemState = jsonProcessor.getSystemState(receivedContent);
        int valveValue = valveController.getValveValueForStateAsInt(systemState);
        updateValvePosition(valveValue);
        break;
    }
}

void WaterChannelController::checkButtonStatus()
{
    static unsigned long timeOfLastButtonPress = 0;

    int currentButtonState = digitalRead(buttonPin);
    if (currentButtonState == HIGH && millis() - timeOfLastButtonPress > DEBOUNCE_DELAY)
    {
        toggleState();
        timeOfLastButtonPress = millis();
    }
}

void WaterChannelController::toggleState()
{
    state = (state == State::MANUAL) ? State::AUTOMATIC : State::MANUAL;
}