#include "../api/LCD.h"

LCD::LCD(int address, int columns, int rows) : lcd(address, columns, rows)
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void LCD::clear()
{
    lcd.clear();
}

void LCD::write(const char *string, int start_col, int start_rows)
{
    lcd.setCursor(start_col, start_rows);
    lcd.print(string);
}