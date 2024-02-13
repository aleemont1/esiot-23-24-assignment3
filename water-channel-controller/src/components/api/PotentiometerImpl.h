#ifndef __POTENTIOMETERIMPL__
#define __POTENTIOMETERIMPL__

#include "Potentiometer.h"

/**
 * @brief This class is a concrete implementation of the Potentiometer abstract class.
 *
 * The PotentiometerImpl class provides the specific implementation for a potentiometer.
 * It inherits from the Potentiometer abstract class and implements the position and moved methods.
 */
class PotentiometerImpl : public Potentiometer
{
public:
    /**
     * @brief Construct a new PotentiometerImpl object.
     *
     * @param pin The pin number to which the potentiometer is connected.
     * @param tolerance The tolerance value for detecting movement in the potentiometer.
     */
    PotentiometerImpl(int pin, int tolerance);

    /**
     * @brief Get the current position of the potentiometer.
     *
     * @return The current position of the potentiometer as an unsigned integer.
     */
    unsigned int position() override;

    /**
     * @brief Check if the potentiometer has been moved.
     *
     * @return True if the potentiometer has been moved, false otherwise.
     */
    bool moved() override;

private:
    int pin;                          ///< The pin number to which the potentiometer is connected.
    int tolerance;                    ///< The tolerance value for detecting movement in the potentiometer.
    unsigned int oldValue;            ///< The old position value of the potentiometer.
    const int MIN_ANALOG_READ = 0;    ///< The minimum value that can be read from the analog pin.
    const int MAX_ANALOG_READ = 1000; ///< The maximum value that can be read from the analog pin.
    const int MIN_POSITION = 0;       ///< The minimum position value of the potentiometer.
    const int MAX_POSITION = 100;     ///< The maximum position value of the potentiometer.
};

#endif // __POTENTIOMETERIMPL__