#include "InputTask.h"

#include "Arduino.h"

#include "WaterChannelController.h"
#include "components/api/ButtonImpl.h"
#include "components/api/PotentiometerImpl.h"
#include "system/Logger.h"

InputTask::InputTask(int period, WaterChannelController *WaterChannelController, int buttonPin, int potPin)
    : Task(period),
      waterChannelController(WaterChannelController),
      pressed(false),
      button(new ButtonImpl(buttonPin, true)),
      potentiometer(new PotentiometerImpl(potPin, 20)),
      oldPotPos(0),
      lastButtonPress(0)
{
    waterChannelController->posChange = true;
    oldPotPos = potentiometer->position();
}

void InputTask::tick()
{
    handleButtonPress();
    handleModeChange();
    updatePressedState();
};

void InputTask::handleButtonPress()
{
    unsigned long currentMillis = millis();
    if (button->isPressed() && !this->pressed && (currentMillis - lastButtonPress > DEBOUNCE_DELAY))
    {
        lastButtonPress = currentMillis;
        toggleMode();
        waterChannelController->commChange = true;
    }
}

void InputTask::toggleMode()
{
    waterChannelController->activeMode = waterChannelController->activeMode == Mode::MANUAL ? Mode::AUTOMATIC : Mode::MANUAL;
}

void InputTask::handleModeChange()
{
    if (waterChannelController->activeMode == Mode::MANUAL)
    {
        handleManualMode();
    }
    else if (waterChannelController->activeMode == Mode::AUTOMATIC)
    {
        handleAutomaticMode();
    }
}

void InputTask::handleManualMode()
{
    if (potentiometer->moved())
    {
        waterChannelController->activePosition = potentiometer->position();
        waterChannelController->posChange = true;
    }
}

void InputTask::handleAutomaticMode()
{
    String receivedContent = messageReceiver.getReceivedContent();
    String systemState = jsonProcessor.getSystemState(receivedContent);
    // int valveValue = TODO: get valve value from system state
    // waterChannelController->activePosition = valveValue;
}

void InputTask::updatePressedState()
{
    this->pressed = button->isPressed();
}