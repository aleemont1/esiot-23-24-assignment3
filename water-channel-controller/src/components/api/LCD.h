#ifndef __LCD__
#define __LCD__

#include "Display.h"
#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

/**
 * @brief This class is a concrete implementation of the Display interface for an LCD.
 *
 * The Lcd class provides the functionality to interact with an LCD display using the LiquidCrystal_I2C library.
 * It allows to clear the display, print a new line, and show a message on the display.
 */
class Lcd : public Display
{
public:
    /**
     * @brief Construct a new Lcd object.
     *
     * @param lcdAddr The I2C address of the LCD display.
     * @param lcdCols The number of columns in the LCD display.
     * @param lcdRows The number of rows in the LCD display.
     */
    Lcd(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows);

    /**
     * @brief Clear the LCD display.
     * This method clears the LCD display and moves the cursor to the home position.
     */
    void clear() override;

    /**
     * @brief Move the cursor to the next line on the LCD display.
     */
    void ln() override;

    /**
     * @brief Show a message on the LCD display.
     * If the message is longer than the number of columns in the display, it will be split into two lines.
     *
     * @param message The message to be displayed.
     */
    void show(String message) override;

private:
    LiquidCrystal_I2C *lcd; ///< Pointer to the LiquidCrystal_I2C object that represents the LCD display.
    uint8_t activeRow{0};   ///< The current active row in the display where the next characters will be printed.
    uint8_t totalCols;      ///< The total number of columns in the LCD display.
};

#endif // __LCD__