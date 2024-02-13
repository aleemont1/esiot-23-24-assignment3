#ifndef __DISPLAY_CLASS__
#define __DISPLAY_CLASS__

#include "Arduino.h"

/**
 * @class Display
 * @brief This is an abstract base class for different types of displays.
 *
 * This class provides a common interface for different types of displays that can be used in Arduino projects.
 * Any specific display class should inherit from this class and implement the pure virtual functions.
 */
class Display
{
public:
    /**
     * @brief Clears the display.
     *
     * This is a pure virtual function that needs to be implemented by any class that inherits from Display.
     */
    virtual void clear() = 0;

    /**
     * @brief Shows a message on the display.
     *
     * @param msg The message to be displayed.
     *
     * This is a pure virtual function that needs to be implemented by any class that inherits from Display.
     */
    virtual void show(String msg) = 0;

    /**
     * @brief Moves the cursor to the next line on the display.
     *
     * This is a pure virtual function that needs to be implemented by any class that inherits from Display.
     */
    virtual void ln() = 0;
};

#endif // __DISPLAY_CLASS__