#include "BAREMETAL_pins.h"
#include "ESC_logic.h"

extern motor_state_t MotorState;

void interrupt ESC_ISR(void)
{
    /* Timer1 overflow */
    if (PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;    //clear interrupt flag
        commutate();
//        if (MotorState.isComparatorPhaseNext)
//        {
//            
//        }
    }
    
    /* Comparator interrupt */
    if (PIR2bits.C1IF)
    {
        PIR2bits.C1IF = 0;      //clear interrupt flag
        //...
    }
}