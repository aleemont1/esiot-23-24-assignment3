#include "LcdTask.h"

LcdTask::LcdTask(int period, WaterChannelController *waterChannelController, uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows)
    : Task(period),
      waterChannelController(waterChannelController),
      lcd(new Lcd(lcdAddr, lcdCols, lcdRows)),
      colDisplay(lcdCols)
{
    initializeLcd();
}

void LcdTask::tick()
{
    displayModeAndPosition();
}

void LcdTask::initializeLcd()
{
    lcd->clear();
    lcd->show("Water Channel Controller");
}

void LcdTask::displayModeAndPosition()
{
    const String mode = getModeString();
    const String position = getPositionString();
    String message = mode + position;
    lcd->show(message);
}

String LcdTask::getModeString()
{
    return (waterChannelController->activeMode == Mode::AUTOMATIC) ? "Automatic: " : "Manual: ";
}

String LcdTask::getPositionString()
{
    return String(waterChannelController->activePosition);
}