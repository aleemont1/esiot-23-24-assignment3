#ifndef __WATERCHANNELCONTROLLER__
#define __WATERCHANNELCONTROLLER__

#include "Arduino.h"

/**
 * @brief Enum for the modes of the water channel controller.
 *
 * This enum represents the possible modes of the water channel controller: Automatic and Manual.
 */
enum class Mode
{
    AUTOMATIC,
    MANUAL
};

/**
 * @brief A controller for a water channel.
 *
 * This class represents a controller for a water channel. The controller can be in one of two modes: Automatic or Manual.
 * The controller has an active position and flags to indicate whether the communication or position has changed.
 */
class WaterChannelController
{
public:
    bool commChange;             ///< Flag to indicate whether the communication has changed.
    bool posChange;              ///< Flag to indicate whether the position has changed.
    Mode activeMode;             ///< The active mode of the controller.
    unsigned int activePosition; ///< The active position of the controller.
};

#endif // __WATERCHANNELCONTROLLER__