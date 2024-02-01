#include "../api/AbstractButton.h"

AbstractButton::AbstractButton() : lastTimeSync(0) {}

void AbstractButton::updateSyncTime(long time)
{
    lastTimeSync = time;
}

long AbstractButton::getLastSyncTime()
{
    return lastTimeSync;
}