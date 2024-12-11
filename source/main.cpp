// This is the main file for the project. It contains the main loop and the main function.
// More information about avr is available at https://www.nongnu.org/avr-libc/user-manual/index.html
// https://github.com/avrdudes/avr-libc

#include "main.h"


int main(void)
{

    SetProject(); // Set the project function

    while(1) {
        // Same as loop in Arduino
        (*pfProject) (); // Call the project function  
    } 
    return 0; // We will never get here!
}

void SetProject()
{
        #if ( PROJECT == PROJECT_BLINK_LED )
    pfProject = ProjectBlinkLed; // Set the project function
        #elif ( PROJECT == PROJECT_DISPLAY_CLOCK  )
    pfProject = ProjectDisplayClock; // Set the project function
        #elif ( PROJECT == PROJECT_PS2 )
    pfProject = ProjectPS2; // Set the project function
        #else // PROJECT == PROJECT_INVALID
    #error('Unsupported PROJECT')
        #endif // PROJECT == ??
}