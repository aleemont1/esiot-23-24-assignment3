#include "../api/LCD.h"

#include <Arduino.h>

Lcd::Lcd(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows)
    : lcd(new LiquidCrystal_I2C(lcdAddr, lcdCols, lcdRows)),
      totalCols(lcdCols)
{
    lcd->init();
    lcd->backlight();
}
void Lcd::clear()
{
    activeRow = 0;
    lcd->clear();
    lcd->setCursor(0, activeRow);
}
void Lcd::show(String message)
{
    String padding = "";
    for (size_t i = message.length(); i < totalCols * 2; i++)
    {
        padding = padding + " ";
    }
    String paddedMessage = message + padding;
    lcd->print(paddedMessage.substring(0, totalCols));
    this->ln();
    lcd->print(paddedMessage.substring(totalCols));
    lcd->setCursor(0, 0);
}

void Lcd::ln()
{
    activeRow++;
    lcd->setCursor(0, activeRow);
}