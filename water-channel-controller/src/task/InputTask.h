#ifndef __INPUTTASK__
#define __INPUTTASK__

#include "WaterChannelController.h"
#include "system/taskWithState.h"
#include "system/task.h"
#include "components/api/ServoMotor.h"
#include "components/api/Button.h"
#include "components/api/Potentiometer.h"
#include "serial_communication/Client-Arduino/MessageReceiver.h"
#include "serial_communication/Client-Arduino/JsonProcessor.h"
#include "serial_communication/Client-Arduino/ValveController.h"

class InputTask : public Task
{
public:
    InputTask(int period, WaterChannelController *WaterChannelController, int buttonPin, int potPin);
    void tick() override;
    void handleButtonPress();
    void handleModeChange();
    void toggleMode();
    void updatePressedState();
    void handleManualMode();
    void handleAutomaticMode();

private:
    WaterChannelController *waterChannelController;
    MessageReceiver messageReceiver;
    JsonProcessor jsonProcessor;
    ValveController valveController;
    bool pressed;
    Button *button;
    Potentiometer *potentiometer;
    unsigned int oldPotPos;
    const unsigned long DEBOUNCE_DELAY = 50;
    unsigned long lastButtonPress;
};

#endif // __INPUTTASK__