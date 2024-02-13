#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "WaterChannelController.h"
#include "components/api/Display.h"
#include "system/task.h"

class LcdTask : public Task
{
public:
    LcdTask(int period,
            WaterChannelController *WaterChannelController,
            uint8_t lcd_Addr,
            uint8_t lcd_cols,
            uint8_t lcd_rows);
    void tick() override;

private:
    WaterChannelController *waterChannelController;
    Display *lcd;
    unsigned short colDisplay;
};
#endif // __LCD_TASK__