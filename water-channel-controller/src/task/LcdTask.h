#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "WaterChannelController.h"
#include "components/api/Display.h"
#include "system/Task.h"
#include "components/api/LCD.h"

/**
 * @brief Handles the LCD display tasks of the system.
 *
 * This class is responsible for handling all the LCD display tasks of the system. It extends the Task class and overrides the tick method.
 * It also provides methods to initialize the LCD, display the mode and position, and get string representations of the mode and position.
 */
class LcdTask : public Task
{
public:
    /**
     * @brief Construct a new Lcd Task object
     *
     * @param period The period of the task.
     * @param WaterChannelController Pointer to the WaterChannelController object.
     * @param lcdAddr The I2C address of the LCD.
     * @param lcdCols The number of columns of the LCD.
     * @param lcdRows The number of rows of the LCD.
     */
    LcdTask(int period, WaterChannelController *WaterChannelController, uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows);

    /**
     * @brief Overridden tick method from the Task class.
     */
    void tick() override;

    /**
     * @brief Initializes the LCD.
     */
    void initializeLcd();

    /**
     * @brief Displays the mode and position on the LCD.
     */
    void displayModeAndPosition();

    /**
     * @brief Returns a string representation of the current mode.
     *
     * @return String The current mode as a string.
     */
    String getModeString();

    /**
     * @brief Returns a string representation of the current position.
     *
     * @return String The current position as a string.
     */
    String getPositionString();

private:
    WaterChannelController *waterChannelController; ///< Pointer to the WaterChannelController object.
    Display *lcd;                                   ///< Pointer to the Display object.
    unsigned short colDisplay;                      ///< The number of columns of the LCD.
};

#endif // __LCD_TASK__