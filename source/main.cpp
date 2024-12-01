// This is the main file for the project. It contains the main loop and the main function.
// More information about avr is available at https://www.nongnu.org/avr-libc/user-manual/index.html
// https://github.com/avrdudes/avr-libc

#include "main.h"

    #if ( PROJECT == PROJECT_BLINK_LED )
#include "project/BlinkLed.cpp"
    #elif ( PROJECT == PROJECT_DISPLAY_CLOCK  )
#include "project/DisplayClock.cpp"
    #else // PROJECT == PROJECT_INVALID
// Invalid project name
#error('Unsupported PROJECT')
    #endif // PROJECT == ??

static void (*pfProject) (void); // Pointer to the function to be called by different project
static void SetProject(void);    // Set pfProject to call project function

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
    #else // PROJECT == PROJECT_INVALID
        // Invalid project name
    #error('Unsupported PROJECT')
    #endif // PROJECT == ??
}