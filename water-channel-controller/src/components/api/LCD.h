#ifndef __DISPLAY__
#define __DISPLAY__

#include "Display.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Lcd : public Display
{
private:
    LiquidCrystal_I2C *lcd;
    uint8_t active_row{0};
    uint8_t total_cols;

public:
    Lcd(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void clear() override;
    void ln() override;
    void show(String msg) override;
};

#endif