#include "ProjectPrivate.h"

#define BLINK_PERIOD_LOW 50000         // 0.05 second
#define BLINK_PERIOD_HIGH 1000000       // 1 second


static void InitBlinkLed(long timer1_period);
static void ProjectBlinkLed(void);