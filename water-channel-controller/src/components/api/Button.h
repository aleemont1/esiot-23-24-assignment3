#ifndef __BUTTON__
#define __BUTTON__

/**
 * @brief This class represents a Button.
 *
 * The Button class is an abstract class that provides the basic functionalities of a button.
 * A button is a simple input device commonly used in electronic devices.
 * The class is designed to be inherited by specific implementations of buttons.
 */
class Button
{
public:
    /**
     * @brief Check if the button is currently pressed.
     *
     * This is a pure virtual function, to be implemented by derived classes.
     *
     * @return True if the button is currently pressed, false otherwise.
     */
    virtual bool isPressed() = 0;
};

#endif // __BUTTON__