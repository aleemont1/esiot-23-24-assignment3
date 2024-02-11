#include "WaterChannelController.h"

WaterChannelController::WaterChannelController(int servoPin, int buttonPin, int potentiometerPin, int lcdAddr, int lcdColumns, int lcdRows)
    : buttonPin(buttonPin), potentiometerPin(potentiometerPin), manualMode(false), lcd(lcdAddr, lcdColumns, lcdRows), currentValveOpeningLevel(0)
{
    valveServo.attach(servoPin);
}

void WaterChannelController::initialize()
{
    initializeButton();
    initializeValve();
    initializeLcd();
    updateLCD();
    reading();
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

// TODO: Implement the parseValveValue method
void WaterChannelController::updateValvePosition(int valveOpeningLevel)
{
    int servoAngle = mapValveOpeningLevelToServoAngle(valveOpeningLevel);
    valveServo.write(servoAngle);
    currentValveOpeningLevel = valveOpeningLevel;
    updateLCD();
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
    if (state == State::MANUAL)
    {
        manualControl();
    }
    else if (state == State::AUTOMATIC)
    {
        updateValvePosition(50); // TODO: Replace with actual logic to determine valve opening level like a getter for the valve opening level
    }
}

void WaterChannelController::checkButtonStatus()
{
    static unsigned long lastButtonPress = 0;

    int buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH && millis() - lastButtonPress > DEBOUNCE_DELAY)
    {
        toggleState();
        lastButtonPress = millis();
    }
}

void WaterChannelController::toggleState()
{
    state = (state == State::MANUAL) ? State::AUTOMATIC : State::MANUAL;
}