    #ifndef headerfiles
#include "IoPrivate.h"
    #endif // headerfiles


// Build-in LED

static void io_ToggleLed(void)
{
    TCNT1 = 0; // Reset the counter
    PORTB ^= _BV(PORTB5); // Toggle the LED
}

void io_InitLed(void)
{
    DDRB |= _BV(DDB5); // Set LED as an output
    PORTB |= _BV(PORTB5); // Turn on the LED
}