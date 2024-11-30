// Built-in LED related
typedef enum {  TIMER1_IDLE = 0,
                TIMER1_WAIT_FOR_ISR = 1,
                TIMER1_RUN  = 2,
} timer1_isr_state;