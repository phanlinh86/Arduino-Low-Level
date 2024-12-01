// AVR libraries
#include <avr/io.h>
#include <avr/interrupt.h>


// Interrupt
#include "int/InterruptTimer1.cpp"


// IO
#include "io/Uart.cpp"

// Project name
#define PROJECT_INVALID            0
#define PROJECT_BLINK_LED          1
#define PROJECT_DISPLAY_CLOCK      2

    #ifndef PROJECT
#define PROJECT PROJECT_INVALID
    #endif // PROJECT


// Project compilation time
    #ifndef HOUR
#define HOUR 0
    #endif // HOUR

    #ifndef MINUTE
#define MINUTE 0
    #endif // MINUTE

    #ifndef SECOND
#define SECOND 0
    #endif // SECOND