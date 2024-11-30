#include "BlinkLed.h"
#include <stdio.h>

// Project functions - Blinking Led
void ProjectBlinkLed(void)
{
    static long timer1_period = BLINK_PERIOD_LOW; // 1 second
    char buffer[100];
    if (eProjectState == PROJECT_INIT)
    {
        UartInit(9600);
        InitBlinkLed(BLINK_PERIOD_LOW);
        eProjectState = PROJECT_LOOP;
    }
    else
    {
        if (GetTimer1Counter() * GetPeriodTimer1() >= BLINK_PERIOD_HIGH * 2)
        {
            // Change the period of the blinking led
            sprintf(buffer, "Change the period from %lu to %lu\n", timer1_period, timer1_period/2);
            UartTransmitString(buffer);            
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
    InitLed();     
    pfServiceTimer1 = BlinkLed;
    SetTimer1Period(timer1_period);
    SetTimer1Counter(0);
    InitTimer1();
}

// Build-in LED
static void BlinkLed(void)
{
    TCNT1 = 0; // Reset the counter
    PORTB ^= _BV(PORTB5); // Toggle the LED
}

void InitLed(void)
{
    DDRB |= _BV(DDB5); // Set LED as an output
    PORTB |= _BV(PORTB5); // Turn on the LED
}