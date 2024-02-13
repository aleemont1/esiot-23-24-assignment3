#ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Button.h"
#include "Arduino.h"

/**
 * @class ButtonImpl
 * @brief This class is a concrete implementation of the Button abstract class.
 *
 * The ButtonImpl class provides the specific implementation for a button in an Arduino context.
 * It inherits from the Button abstract class and implements the isPressed method.
 */
class ButtonImpl : public Button
{
public:
    /**
     * @brief Construct a new ButtonImpl object.
     *
     * @param pin The Arduino pin number to which the button is connected.
     * @param pullup A boolean indicating if the button has a pullup resistor or not.
     *               True if the button has a pullup resistor, false otherwise.
     */
    ButtonImpl(int pin, bool pullup);

    /**
     * @brief Check if the button is currently pressed.
     *
     * @return true If the button is currently pressed.
     * @return false If the button is not currently pressed.
     */
    bool isPressed() override;

private:
    int pin;             ///< The Arduino pin number to which the button is connected.
    bool pullup;         ///< A boolean indicating if the button has a pullup resistor or not.
    bool pressed{false}; ///< A boolean indicating if the button is currently pressed or not. Initialized to false.
};

#endif // __BUTTONIMPL__