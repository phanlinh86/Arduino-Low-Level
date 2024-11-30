// This is the main file for the project. It contains the main loop and the main function.
// More information about avr is available at https://www.nongnu.org/avr-libc/user-manual/index.html
// https://github.com/avrdudes/avr-libc

#include "main.h"

static void init(void);
static void initToggleLed(long timer1_period);


int main(void)
{
    
    long timer1_period = 1000000; // 1 second
    init(); // Same as setup in Arduino  
    while(1) { 
        // Same as loop in Arduino
        if (GetTimer1Counter() * GetPeriodTimer1() >= 2000000)
        {
            timer1_period /= 4;
            if (timer1_period <= 100000)
            {
                timer1_period = 1000000;
            }
            initToggleLed(timer1_period);
        }
        DoTimer1Isr();        
    } 
    return 0; // We will never get here!
}

static void init(void)
{
    initToggleLed(100000);
}

static void initToggleLed(long timer1_period)
{           
    pfServiceTimer1 = io_ToggleLed;
    SetTimer1Period(timer1_period);
    SetTimer1Counter(0);
    io_InitLed();
    InitTimer1();
}
