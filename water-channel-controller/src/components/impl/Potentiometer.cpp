#include "../api/PotentiometerImpl.h"

#include "Arduino.h"

PotentiometerImpl::PotentiometerImpl(int pin, int tolerance) : pin(pin), tolerance(tolerance), oldValue(analogRead(pin))
{
    pinMode(pin, INPUT);
}

unsigned int PotentiometerImpl::position()
{
    int val = map(analogRead(pin), MIN_ANALOG_READ, MAX_ANALOG_READ, MIN_POSITION, MAX_POSITION);
    if (val < MIN_POSITION)
        val = MIN_POSITION;
    if (val > MAX_POSITION)
        val = MAX_POSITION;
    return val;
}

bool PotentiometerImpl::moved()
{
    unsigned int val = analogRead(pin);
    /*
        NOTE: this ensures correct subtraction operation between oldValue and val as they are unsigned integers
        and direct subtraction could lead to unexpected results if val is less than oldValue.
    */
    bool hasMoved = abs(static_cast<int>(oldValue) - static_cast<int>(val)) > tolerance;
    oldValue = val;
    return hasMoved;
}