#ifndef __ABSTRACT_BUTTON_H__
#define __ABSTRACT_BUTTON_H__

#include "Arduino.h"

/**
 * @class AbstractButton
 * @brief This class provides an abstract interface for a button.
 *
 * The AbstractButton class provides a common interface for different types of buttons.
 * It includes methods to check if the button is pressed and to synchronize the button state.
 */
class AbstractButton
{

public:
    /**
     * @brief Construct a new AbstractButton object.
     *
     * This is a default constructor for creating a new AbstractButton object.
     */
    AbstractButton();

    /**
     * @brief Check if the button is pressed.
     *
     * This is a pure virtual method that must be implemented by any class that inherits from AbstractButton.
     * It should return true if the button is currently pressed, and false otherwise.
     *
     * @return true if the button is pressed, false otherwise.
     */
    virtual bool isPressed() = 0;

    /**
     * @brief Synchronize the button state.
     *
     * This method is used to update the button state. It should be called regularly to ensure that the button state is up-to-date.
     */
    virtual void sync();

    /**
     * @brief Get the last synchronization time.
     *
     * This method returns the time (in milliseconds since the program started) when the button state was last synchronized.
     *
     * @return The last synchronization time in milliseconds.
     */
    long getLastSyncTime();

protected:
    /**
     * @brief Update the synchronization time.
     *
     * This method updates the last synchronization time to the specified value.
     *
     * @param time The new synchronization time in milliseconds.
     */
    void updateSyncTime(long time);

private:
    long lastTimeSync; ///< The time (in milliseconds since the program started) when the button state was last synchronized.
};

#endif // __ABSTRACT_BUTTON_H__