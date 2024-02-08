#include "ValveController.h"

ValveController::ValveController() {}

ValveController::~ValveController() {}

/**
 * @struct StatusValvePair
 * @brief This struct represents a mapping between a system state and a valve value.
 *
 * It contains two fields: systemState and valveValue. The systemState field represents the state of the system,
 * and the valveValue field represents the corresponding valve value for that state.
 */
struct StatusValvePair
{
    String systemState;
    String valveValue;
};

/**
 * @brief This array contains the predefined mappings of system states to valve values.
 *
 * Each element in the array is a StatusValvePair struct, which contains a system state and the corresponding valve value.
 * The array is used by the getValveValueForState method to find the valve value for a given system state.
 */
StatusValvePair statusValvePairs[] = {
    {"NORMAL", "25"},
    {"ALARM_TOO_LOW", "0"},
    {"PRE_ALARM_TOO_HIGH", "40"},
    {"ALARM_TOO_HIGH", "50"},
    {"ALARM_TOO_HIGH_CRITIC", "100"},
    {"ping", "ping"}};

String ValveController::getValveValueForState(String systemState)
{
    for (StatusValvePair pair : statusValvePairs)
    {
        if (pair.systemState == systemState)
        {
            return pair.valveValue;
        }
    }
    return "Unknown system state";
}

String ValveController::setValveValue(String systemState)
{
    String valveValue = getValveValueForState(systemState);
    return valveValue;
}