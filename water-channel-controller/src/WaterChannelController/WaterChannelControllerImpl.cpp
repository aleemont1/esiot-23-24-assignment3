#include "WaterChannelController.h"

WaterChannelController::WaterChannelController(int servoPin, int buttonPin, int potentiometerPin, int lcdAddr, int lcdColumns, int lcdRows)
    : buttonPin(buttonPin), potentiometerPin(potentiometerPin), manualMode(false), lcd(lcdAddr, lcdColumns, lcdRows), currentValveOpeningLevel(0)
{
    valveServo.attach(servoPin);
}

void WaterChannelController::initialize()
{
    pinMode(buttonPin, INPUT);
    valveServo.write(MIN_SERVO_ANGLE); // Initially the valve is assumed as closed
    lcd.begin(columns, rows);
    updateLCD();
}

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
    lcd.print(manualMode ? "MANUAL" : "AUTOMATIC");
}

void WaterChannelController::manualControl()
{
    if (manualMode)
    {
        int potentiometerValue = analogRead(potentiometerPin);
        int valveOpeningLevel = map(potentiometerValue, MIN_POTENTIOMETER_VALUE, MAX_POTENTIOMETER_VALUE, MIN_VALVE_OPENING_LEVEL, MAX_VALVE_OPENING_LEVEL);
        updateValvePosition(valveOpeningLevel);
    }
}