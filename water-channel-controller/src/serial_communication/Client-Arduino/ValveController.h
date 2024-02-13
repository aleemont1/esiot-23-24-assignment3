// #ifndef __VALVECONTROLLER_H__
// #define __VALVECONTROLLER_H__

// #include "Arduino.h"
// class ValveController
// {
// public:
//     /**
//      * @brief Construct a new Valve Controller object.
//      *
//      */
//     ValveController();

//     /**
//      * @brief Destroy the Valve Controller object.
//      *
//      */
//     ~ValveController();

//     /**
//      * @brief Set the valve value based on the system state.
//      *
//      * This method takes a string representing the system state and sets the valve value accordingly.
//      * The mapping from system states to valve values is predefined.
//      *
//      * @param systemState A string representing the system state.
//      */
//     String setValveValue(String systemState);

//     /**
//      * @brief This method is used to get the valve value for a given system state.
//      *
//      * It uses a predefined mapping of system states to valve values. If the system state is not found in the mapping,
//      * it returns "Unknown system state".
//      *
//      * @param systemState The system state for which to get the valve value.
//      * @return String The valve value for the given system state, or "Unknown system state" if the system state is not found in the mapping.
//      */
//     String getValveValueForState(String systemState);

//     /**
//      * @brief This method is used to parse the valve value from a string to an integer.
//      * It is used to convert the valve value received from the server to an integer that can be used to control the valve position.
//      *
//      * @param valveValue
//      * @return int
//      */
//     int parseValveValue(String valveValue);

//     /**
//      * @brief Get the valve value for a given system state as an integer value so that it can be used to control the valve position.
//      *
//      * @param systemState The system state for which to get the valve value.
//      * @return int The valve value for the given system state as an integer.
//      */
//     int getValveValueForStateAsInt(String systemState);
// };

// #endif // __VALVECONTROLLER_H__