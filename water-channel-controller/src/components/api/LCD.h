#ifndef __LCD_H__
#define __LCD_H__

#include "LiquidCrystal_I2C.h"
#include "Arduino.h"
#include "Wire.h"

/**
 * @brief This class provides an interface for controlling an LCD display
 * using the I2C protocol.
 */
class LCD
{
public:
    /**
     * @brief Construct a new LCD object.
     *
     * @param address The I2C address of the LCD display.
     * @param columns The number of columns in the LCD display.
     * @param rows The number of rows in the LCD display.
     */
    LCD(int address, int columns, int rows);

    /**
     * @brief Write a string to the LCD display at a specified location.
     *
     * @param string The string to write to the display.
     * @param start_col The column at which to start writing the string.
     * @param start_rows The row at which to start writing the string.
     */
    void write(const char *string, int start_col, int start_rows);

    /**
     * @brief Clear the LCD display.
     */
    void clear();

protected:
    /**
     * @brief An instance of the LiquidCrystal_I2C class used to control the LCD display.
     */
    LiquidCrystal_I2C lcd;
};

#endif // __LCD_H__