#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "../api/AbstractButton.h"
#include "Arduino.h"

/**
 * @class Button
 * @brief This class represents a physical button connected to a digital I/O pin.
 *
 * The Button class extends the AbstractButton class and provides an implementation
 * for a physical button connected to a digital I/O pin. It includes methods to check
 * if the button is pressed and to synchronize the button state.
 */
class Button : public AbstractButton
{

public:
    /**
     * @brief Construct a new Button object.
     *
     * This constructor creates a new Button object associated with a specific digital I/O pin.
     *
     * @param pin The digital I/O pin number to which the button is connected.
     */
    Button(int pin);

    /**
     * @brief Check if the button is pressed.
     *
     * This method returns true if the button is currently pressed, and false otherwise.
     *
     * @return true if the button is pressed, false otherwise.
     */
    bool isPressed();

    /**
     * @brief Synchronize the button state.
     *
     * This method is used to update the button state. It should be called regularly to ensure that the button state is up-to-date.
     */
    void sync();

    /**
     * @brief Synchronize the button state.
     *
     * This method is used to update the button state. It should be called regularly to ensure
     * that the button state is up-to-date. It reads the current state of the digital I/O pin
     * to which the button is connected and updates the internal state accordingly.
     */
private:
    int pin;                                 ///< The digital I/O pin number to which the button is connected.
    const unsigned long DEBOUNCE_DELAY = 50; ///< The debounce delay in milliseconds.
    unsigned long lastDebounceTime = 0;      ///< The last time the button state was updated.
    bool pressed;                            ///< The current state of the button (true = pressed, false = not pressed).
};

#endif // __BUTTON_H__