#include "LcdTask.h"

#include "components/api/LCD.h"

LcdTask::LcdTask(int period, WaterChannelController *waterChannelController, uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : Task(period), waterChannelController(waterChannelController), lcd(new Lcd(lcd_Addr, lcd_cols, lcd_rows)), colDisplay(lcd_cols)
{
    this->lcd->clear();
    this->lcd->show("Water Channel Controller");
}

void LcdTask::tick()
{
    const String mode = waterChannelController->activeMode == Mode::AUTOMATIC ? "Automatic: " : "Manual: ";
    const String position = String(waterChannelController->activePosition);
    String message = mode + position;
    lcd->show(message);
}