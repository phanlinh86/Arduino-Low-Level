#include "DisplayClock.h"

void ProjectDisplayClock(void)
{
    // Display clock by sending to UART
    // The clock is updated every 1 second
    static long timer1_period = 1000000; // 1 second

    if (eProjectState == PROJECT_INIT)
    {
        UartInit(9600);
        InitDisplayClock(timer1_period);
        eProjectState = PROJECT_LOOP;
    }
    else // eProjectState == PROJECT_LOOP
    {
        DoTimer1Isr();
    }
}


void InitDisplayClock(long timer1_period)
{
    pfServiceTimer1 = DisplayClock;
    SetTimer1Period(timer1_period);
    SetTimer1Counter(0);
    InitTimer1();
}


void DisplayClock(void)
{
    // Display the clock
    char buffer[100];

    second++;
    if (second >= 60)
    {
        second = 0;
        minute++;
        if (minute >= 60)
        {
            minute = 0;
            hour++;
            if (hour >= 24)
            {
                hour = 0;
            }
        }
    }
    sprintf(buffer, "Time: %02d:%02d:%02d\n", hour, minute, second);
    UartTransmitString(buffer);
}
