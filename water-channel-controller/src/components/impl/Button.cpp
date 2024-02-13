#include "../api/ButtonImpl.h"

ButtonImpl::ButtonImpl(int pin, bool pullup) : pin(pin), pullup(pullup)
{
    if (pullup)
    {
        pinMode(pin, INPUT_PULLUP);
    }
    else
    {
        pinMode(pin, INPUT);
    }
}

bool ButtonImpl::isPressed()
{
    // if pull up enabled, output reversed
    return digitalRead(pin) ^ this->pullup;
}