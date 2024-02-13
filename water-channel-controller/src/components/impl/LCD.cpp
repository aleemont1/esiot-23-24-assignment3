#include "../api/LCD.h"

#include <Arduino.h>

Lcd::Lcd(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : lcd(new LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)),
      total_cols(lcd_cols)
{
    lcd->init();
    lcd->backlight();
}
void Lcd::clear()
{
    active_row = 0;
    lcd->clear();
    lcd->setCursor(0, active_row);
}
void Lcd::show(String msg)
{
    String padding = "";
    for (size_t i = msg.length(); i < total_cols * 2; i++)
    {
        padding = padding + " ";
    }
    String paddedMessage = msg + padding;
    lcd->print(paddedMessage.substring(0, total_cols));
    this->ln();
    lcd->print(paddedMessage.substring(total_cols));
    lcd->setCursor(0, 0);
}

void Lcd::ln()
{
    active_row++;
    lcd->setCursor(0, active_row);
}