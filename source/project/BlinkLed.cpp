#include "BlinkLed.h"

// Project functions - Blinking Led
void ProjectBlinkLed(void)
{
    static long timer1_period = BLINK_PERIOD_LOW; // 1 second
    if (eProjectState == PROJECT_INIT)
    {
        InitBlinkLed(BLINK_PERIOD_LOW);
        eProjectState = PROJECT_LOOP;
    }
    else
    {
        if (GetTimer1Counter() * GetPeriodTimer1() >= BLINK_PERIOD_HIGH * 2)
        {
            timer1_period /= 2;
            if (timer1_period < BLINK_PERIOD_LOW)
            {
                timer1_period = BLINK_PERIOD_HIGH;
            }
            InitBlinkLed(timer1_period);
        }
        DoTimer1Isr();
    }
}

static void InitBlinkLed(long timer1_period)
{           
    pfServiceTimer1 = io_BlinkLed;
    SetTimer1Period(timer1_period);
    SetTimer1Counter(0);
    io_InitLed();
    InitTimer1();
}
