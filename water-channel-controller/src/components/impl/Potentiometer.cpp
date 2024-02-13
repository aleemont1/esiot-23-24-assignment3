#include "../api/PotentiometerImpl.h"

#include "Arduino.h"

PotentiometerImpl::PotentiometerImpl(int pin, int tolerance) : pin(pin), tolerance(tolerance), oldValue(analogRead(pin))
{
    // pinMode(pin, INPUT);
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
    bool hasMoved = !(oldValue - tolerance < val && oldValue + tolerance > val);
    oldValue = val;
    return hasMoved;
}