// This is the main file for the project. It contains the main loop and the main function.
// More information about avr is available at https://www.nongnu.org/avr-libc/user-manual/index.html
// https://github.com/avrdudes/avr-libc

#include "main.h"
#include "project/BlinkLed.cpp"

static void (*pfProject) (void); // Pointer to the function to be called by different project


int main(void)
{
    pfProject = ProjectBlinkLed; // Set the project function            
    while(1) {        
        // Same as loop in Arduino
        (*pfProject) (); // Call the project function  
    } 
    return 0; // We will never get here!
}