#include "../api/Button.h"

Button::Button(int pin) : pin(pin), lastDebounceTime(0), pressed(false)
{
    pinMode(pin, INPUT);
    sync();
}

bool Button::isPressed()
{
    return pressed;
}

void Button::sync()
{
    // Read the state of the button

    bool reading = digitalRead(pin) == HIGH;

    // Check if the button's state has changed
    if (reading != pressed)
    {
        // Reset the debounce timer
        lastDebounceTime = millis();
    }

    // If the button's state has been stable for longer than the debounce delay, update the button state
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
    {
        pressed = reading;
    }

    updateSyncTime(millis());
}