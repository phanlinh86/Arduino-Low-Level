    #ifndef headerfiles
#include "IntPrivate.h"
    #endif // headerfiles

#define USE_MAX_RESOLUTION 0

#define TIMER1_RESOLUTION 65536   // Timer1 is 16 bit
#define MAX_COUNTER 65535
#define DEFAULT_PERIOD 1000000 // 1 second

timer1_isr_state eTimer1State = TIMER1_IDLE;
long u32_Timer1Period = DEFAULT_PERIOD;   // in microseconds
unsigned int i16_Timer1Counter = 0;                // Counter for the Timer1 ISR

static void DoTimer1Isr(void);
static void InitTimer1(void);
static void WaitTimer1(void);
static void RunTimer1(void);
static void setTimer1State(timer1_isr_state eState);
    #if ( USE_MAX_RESOLUTION == 0 )
static void SetTimer1Period(long microseconds);
// static long GetPeriodTimer1();
static void SetTimer1Counter(unsigned int i16Counter);
static unsigned int GetTimer1Counter();
static void ProgramTimer1(void);
    #endif // USE_MAX_RESOLUTION == 0





static void (*pfServiceTimer1) (void); // Pointer to the function to be called when the Timer1 interrupt occurs

static void DoTimer1Isr(void)
{
    switch (eTimer1State)
    {
        case TIMER1_IDLE:
            // Do nothing till the timer is initialized          
            break;
        case TIMER1_WAIT_FOR_ISR:
            // A middle step to wait for the 1st interrupt to occur
            WaitTimer1();                
            break;
        case TIMER1_RUN:
            // Do nothing, just wait for the interrupt to occur            
            if (i16_Timer1Counter == MAX_COUNTER)
            {
                i16_Timer1Counter = 0;
            }
            break;
        default:
            eTimer1State = TIMER1_IDLE;
            break;
    }
}

static void InitTimer1(void)
{
    cli();                                 // Disable interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
        #if ( USE_MAX_RESOLUTION == 1 )        
    TCCR1B |= (1 << CS11) | (1 << CS10);    // no prescale, full xtal        
    TCNT1 = 20000;   
        #else // USE_MAX_RESOLUTION == 0
    ProgramTimer1();
        #endif // USE_MAX_RESOLUTION == ?
    TIMSK1 = (1 << TOIE1);                  // Overflow interrupt enable 
    sei();                                  // Enable interrupts 
    setTimer1State(TIMER1_WAIT_FOR_ISR);  
}

static void WaitTimer1(void)
{
    if (i16_Timer1Counter >= 1)
    {
        setTimer1State(TIMER1_RUN);
    }
}

    #if ( USE_MAX_RESOLUTION == 0 )  
static void SetTimer1Period(long microseconds)
{
    u32_Timer1Period = microseconds;
}

static long GetPeriodTimer1()
{
    return u32_Timer1Period;
}

static void SetTimer1Counter(unsigned int i16Counter)
{
    i16_Timer1Counter = i16Counter;
}

static unsigned int GetTimer1Counter()
{
    return i16_Timer1Counter;
}

static void ProgramTimer1(void)
{

    /* 
              MAX x Prescale
        Ts = ---------------
              F_CPU x 10^6
    */

    unsigned long cycles = (F_CPU / 2000000) * u32_Timer1Period; // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
    unsigned char clockSelectBits;      

    if(cycles < TIMER1_RESOLUTION)              clockSelectBits = _BV(CS10);              // no prescale, full xtal
    else if((cycles >>= 3) < TIMER1_RESOLUTION) clockSelectBits = _BV(CS11);              // prescale by /8
    else if((cycles >>= 3) < TIMER1_RESOLUTION) clockSelectBits = _BV(CS11) | _BV(CS10);  // prescale by /64
    else if((cycles >>= 2) < TIMER1_RESOLUTION) clockSelectBits = _BV(CS12);              // prescale by /256
    else if((cycles >>= 2) < TIMER1_RESOLUTION) clockSelectBits = _BV(CS12) | _BV(CS10);  // prescale by /1024
    else        cycles = TIMER1_RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10);  // request was out of bounds, set as maximum
        
    TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
    TCCR1B |= clockSelectBits;                                          // reset clock select register, and starts the clock
    TCNT1 = 0; // Reset the counter    
}
    #endif // USE_MAX_RESOLUTION == 0

static void RunTimer1(void)
{
    // Run the timer service routine
    (*pfServiceTimer1)();
    i16_Timer1Counter++;
}

static void setTimer1State(timer1_isr_state eState)
{
    eTimer1State = eState;
}

ISR (TIMER1_OVF_vect)
{
    RunTimer1();
}
