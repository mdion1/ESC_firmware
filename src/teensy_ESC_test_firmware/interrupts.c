#include "BAREMETAL_pins.h"
#include "ESC_logic.h"
#include <xc.h>

extern motor_state_t MotorState;

void __interrupt() ESC_ISR(void)
{
//    /* Pause timer */
//    static uint8_t timerState = 1;
//    timerState = T1CONbits.TMR1ON;
//    T1CONbits.TMR1ON = 0;
    
    /* Timer1 overflow */
    if (PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;    //clear interrupt flag
        reset_commutation_timer(MotorState.commutationTimerVal);
        commutate();
    }
    
    /* Comparator interrupt */
    else if (PIR2bits.C2IF)
    {
        PIR2bits.C2IF = 0;                                                              //clear interrupt flag
        MotorState.closedLoopCtrl.newComparatorCaptureData = (TMR1H << 8) | TMR1L;      //capture the new zero-crossing time; todo: stop timer?
        //debugging only reset_commutation_timer(MotorState.commutationTimerVal / 2);                    //reset commutation timer to 1/2 * commutation time
        MotorState.closedLoopCtrl.newComparatorCaptureDataFlag = true;
        enable_cmp_interrupt(false);
    }
//    
//    /* Resume timer */
//    T1CONbits.TMR1ON = timerState;
}