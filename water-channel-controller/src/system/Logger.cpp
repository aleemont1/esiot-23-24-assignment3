#include "config.h"

void logger(String log)
{
#ifdef __DEBUG__
    Serial.println(log);
#endif
}
void logger(double log)
{
#ifdef __DEBUG__
    Serial.println(log);
#endif
}
void logger(int log)
{
#ifdef __DEBUG__
    Serial.println(log);
#endif
}