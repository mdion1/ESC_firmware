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
        reset_commutation_timer(MotorState.commutationTimerVal);
    }
    
    /* Comparator interrupt */
    if (PIR2bits.C1IF)
    {
        PIR2bits.C1IF = 0;                                                              //clear interrupt flag
        MotorState.closedLoopCtrl.newComparatorCaptureData = (TMR1H << 8) | TMR1L;      //capture the new zero-crossing time
        reset_commutation_timer(MotorState.commutationTimerVal / 2);                    //reset commutation timer to 1/2 * commutation time
        MotorState.closedLoopCtrl.newComparatorCaptureDataFlag = true;
    }
}