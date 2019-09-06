#include "BAREMETAL_pins.h"
#include "ESC_logic.h"

extern motor_state_t MotorState;

/* Flex timer 1 (commutation timer) overflow interrupt ISR */
void ftm1_isr(void) {
	cli();
	CLEAR_COMMUTATION_TMR_OVF_FLAG()
	commutate();
	sei();
}

void cmp0_isr(void) {
	cli();
	CLEAR_CMP_FLAG()
	//debugging only reset_commutation_timer(MotorState.commutationTimerVal / 2);                    //reset commutation timer to 1/2 * commutation time
	MotorState.closedLoopCtrl.newComparatorCaptureDataFlag = true;
	enable_cmp_interrupt(false);
	sei();
}