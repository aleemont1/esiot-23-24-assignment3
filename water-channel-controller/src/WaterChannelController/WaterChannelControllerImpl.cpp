#include "WaterChannelController.h"

WaterChannelController::WaterChannelController(int servoPin, int buttonPin, int potentiometerPin, int lcdAddr, int lcdColumns, int lcdRows)
    : buttonPin(buttonPin), potentiometerPin(potentiometerPin), manualMode(false), lcd(lcdAddr, lcdColumns, lcdRows), currentValveOpeningLevel(0)
{
    valveServo.attach(servoPin);
}

void WaterChannelController::initialize()
{
    Serial.println("Initializing water channel controller...");
    initializeButton();
    initializeValve();
    initializeLcd();
    updateLCD();
    updateValvePosition(50);
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

void WaterChannelController::updateValvePosition(int valveOpeningLevel)
{
    int servoAngle = mapValveOpeningLevelToServoAngle(valveOpeningLevel);
    valveServo.write(servoAngle);
    currentValveOpeningLevel = valveOpeningLevel;
    updateLCD();
    Serial.print("Valve position updated: ");
    Serial.println(valveOpeningLevel);
}

int WaterChannelController::mapValveOpeningLevelToServoAngle(int valveOpeningLevel)
{
    return map(valveOpeningLevel, MIN_VALVE_OPENING_LEVEL, MAX_VALVE_OPENING_LEVEL, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
}

void WaterChannelController::updateLCD()
{
    Serial.println("Updating LCD...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Valve: ");
    lcd.print(currentValveOpeningLevel);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Mode: ");
    lcd.print(manualMode ? "MANUAL" : "AUTOMATIC");
}

void WaterChannelController::manualControl()
{
    int potentiometerValue = analogRead(potentiometerPin);
    int valveOpeningLevel = map(potentiometerValue, MIN_POTENTIOMETER_VALUE, MAX_POTENTIOMETER_VALUE, MIN_VALVE_OPENING_LEVEL, MAX_VALVE_OPENING_LEVEL);
    updateValvePosition(valveOpeningLevel);
    Serial.print("Manual control activated. Valve opening level: ");
    Serial.println(valveOpeningLevel);
}

void WaterChannelController::reading()
{
    checkButtonStatus();
    if (manualMode == true)
    {
        manualControl();
    }
}

void WaterChannelController::checkButtonStatus()
{
    static unsigned long lastButtonPress = 0;
    unsigned long debounceDelay = 200;

    int buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH && millis() - lastButtonPress > debounceDelay)
    {
        manualMode = !manualMode;
        lastButtonPress = millis();
    }
}