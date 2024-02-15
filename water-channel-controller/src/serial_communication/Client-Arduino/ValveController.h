#ifndef VALVE_CONTROLLER_H
#define VALVE_CONTROLLER_H

#include "Arduino.h"

/**
 * @class ValveController
 * @brief Handles the control of the valve based on the system state.
 *
 * This class is responsible for controlling the valve based on the system state. It provides methods to get and set the valve value for a given system state,
 * parse the valve value, and get the valve value for a state as an integer.
 */
class ValveController
{
public:
    /**
     * @brief Construct a new Valve Controller object
     */
    ValveController();

    /**
     * @brief Destroy the Valve Controller object
     */
    ~ValveController();

    /**
     * @brief Get the Valve Value For a given State
     *
     * @param systemState The system state to get the valve value for.
     * @return String The valve value for the given state.
     */
    String getValveValueForState(String systemState);

    /**
     * @brief Set the Valve Value for a given State
     *
     * @param systemState The system state to set the valve value for.
     * @return String The set valve value.
     */
    String setValveValue(String systemState);

    /**
     * @brief Parse the Valve Value from a string to an integer.
     *
     * @param valveValue The valve value to parse.
     * @return int The parsed valve value.
     */
    int parseValveValue(String valveValue);

    /**
     * @brief Get the Valve Value For a given State as an integer.
     *
     * @param systemState The system state to get the valve value for.
     * @return int The valve value for the given state.
     */
    int getValveValueForStateAsInt(String systemState);

    /**
     * @brief Get the message for manual mode.
     *
     * @return String The message for manual mode.
     */
    String getManualModeMessage();
};

#endif // VALVE_CONTROLLER_H