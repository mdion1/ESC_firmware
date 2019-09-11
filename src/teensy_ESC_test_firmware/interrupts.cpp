#include "BAREMETAL_pins.h"
#include "ESC_logic.h"
#include <Arduino.h>

extern motor_state_t MotorState;
extern bool debuggingBit;

/* Flex timer 1 (commutation timer) overflow interrupt ISR */
void ftm1_isr(void) {
	cli();
	CLEAR_COMMUTATION_TMR_OVF_FLAG()
  reset_commutation_timer(MotorState.commutationTimerVal);
	commutate();
	sei();
}

void cmp0_isr(void) {
	cli();
  
	CLEAR_CMP_FLAG()
	//debugging only reset_commutation_timer(MotorState.commutationTimerVal / 2);                    //reset commutation timer to 1/2 * commutation time
	MotorState.closedLoopCtrl.newComparatorCaptureDataFlag = true;
	MotorState.closedLoopCtrl.newComparatorCaptureData = FTM1_C0V;
	enable_cmp_interrupt(false);
  
	sei();
}
