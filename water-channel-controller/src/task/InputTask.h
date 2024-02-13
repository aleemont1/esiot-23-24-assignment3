#ifndef __INPUT_TASK__
#define __INPUT_TASK__

#include "WaterChannelController.h"
#include "system/taskWithState.h"
#include "system/task.h"
#include "components/api/ServoMotor.h"
#include "components/api/Button.h"
#include "components/api/Potentiometer.h"
#include "serial_communication/Client-Arduino/MessageReceiver.h"
#include "serial_communication/Client-Arduino/JsonProcessor.h"
#include "components/api/ServoMotorImpl.h"

/**
 * @brief Handles the input tasks of the system.
 *
 * This class is responsible for handling all the input tasks of the system. It extends the Task class and overrides the tick method.
 * It also provides methods to handle button press, mode change, manual mode, and automatic mode.
 */
class InputTask : public Task
{
public:
    /**
     * @brief Construct a new Input Task object
     *
     * @param period The period of the task.
     * @param WaterChannelController Pointer to the WaterChannelController object.
     * @param buttonPin The pin number of the button.
     * @param potPin The pin number of the potentiometer.
     */
    InputTask(int period, WaterChannelController *WaterChannelController, int buttonPin, int potPin);

    /**
     * @brief Overridden tick method from the Task class.
     */
    void tick() override;

    /**
     * @brief Handles the button press event.
     */
    void handleButtonPress();

    /**
     * @brief Handles the mode change event caused by the button press.
     */
    void handleModeChange();

    /**
     * @brief Toggles the mode of the system between manual and automatic.
     */
    void toggleMode();

    /**
     * @brief Updates the pressed state of the button based on the current state.
     */
    void updatePressedState();

    /**
     * @brief Handles the manual mode of the system by controlling the motor based on the potentiometer position.
     */
    void handleManualMode();

    /**
     * @brief Handles the automatic mode of the system by controlling the motor based on the water level.
     */
    void handleAutomaticMode();

private:
    WaterChannelController *waterChannelController; ///< Pointer to the WaterChannelController object.
    MessageReceiver messageReceiver;                ///< Object to receive messages from the client.
    JsonProcessor jsonProcessor;                    ///< Object to process JSON messages from the client.
    bool pressed;                                   ///< Flag to indicate if the button is pressed.
    Button *button;                                 ///< Pointer to the Button object.
    Potentiometer *potentiometer;                   ///< Pointer to the Potentiometer object.
    unsigned int oldPotPos;                         ///< Stores the old position of the potentiometer.
    const unsigned long DEBOUNCE_DELAY = 50;        ///< Delay for button debounce, in milliseconds.
    unsigned long lastButtonPress;                  ///< Stores the time of the last button press.
    ServoMotor *motor;                              ///< Pointer to the ServoMotor object.
};

#endif // __INPUT_TASK__