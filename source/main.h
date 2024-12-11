// AVR libraries
#include <avr/io.h>
#include <avr/interrupt.h>


// Interrupt
#include "int/InterruptTimer1.cpp"


// IO
#include "io/Uart.cpp"

// Compilation time
    #ifndef HOUR
#define HOUR 0
    #endif // HOUR

    #ifndef MINUTE
#define MINUTE 0
    #endif // MINUTE

    #ifndef SECOND
#define SECOND 0
    #endif // SECOND

// Project name
#define PROJECT_INVALID            0
#define PROJECT_BLINK_LED          1
#define PROJECT_DISPLAY_CLOCK      2
#define PROJECT_PS2                3

    #ifndef PROJECT
#define PROJECT PROJECT_INVALID
    #endif // PROJECT


    #if ( PROJECT == PROJECT_BLINK_LED )
#include "project/BlinkLed.cpp"
    #elif ( PROJECT == PROJECT_DISPLAY_CLOCK  )
#include "project/DisplayClock.cpp"
    #elif ( PROJECT == PROJECT_PS2 )
#include "project/PS2.cpp"
    #else // PROJECT == PROJECT_INVALID
// Invalid project name
#error('Unsupported PROJECT')
    #endif // PROJECT == ??

static void (*pfProject) (void); // Pointer to the function to be called by different project
static void SetProject(void);    // Set pfProject to call project function
