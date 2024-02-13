#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

/**
 * @brief This class represents a Potentiometer.
 *
 * The Potentiometer class is an abstract class that provides the basic functionalities of a potentiometer.
 * A potentiometer is a three-terminal resistor with a sliding or rotating contact that forms an adjustable voltage divider.
 * The class is designed to be inherited by specific implementations of potentiometers.
 */
class Potentiometer
{
public:
    /**
     * @brief Get the current position of the potentiometer.
     *
     * This is a pure virtual function, to be implemented by derived classes.
     *
     * @return The current position of the potentiometer as an unsigned integer.
     */
    virtual unsigned int position() = 0;

    /**
     * @brief Check if the potentiometer has been moved.
     *
     * This is a pure virtual function, to be implemented by derived classes.
     *
     * @return True if the potentiometer has been moved, false otherwise.
     */
    virtual bool moved() = 0;
};

#endif // __POTENTIOMETER__