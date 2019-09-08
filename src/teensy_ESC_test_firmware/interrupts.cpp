#include "BAREMETAL_pins.h"
#include "ESC_logic.h"
#include <Arduino.h>

extern motor_state_t MotorState;
extern bool debuggingBit;

/* Flex timer 1 (commutation timer) overflow interrupt ISR */
void ftm1_isr(void) {
	cli();
	CLEAR_COMMUTATION_TMR_OVF_FLAG()
	//debugging only commutate();

	/* debugging/testing */
	static int count = 0;
	if (debuggingBit)
	{
		Serial.println("FTM1 ovf");
		if (count++ >= 10)
		{
			debuggingBit = false;
			count = 0;
		}
	}
	/*******************/

	sei();
}

void cmp0_isr(void) {
	cli();
	CLEAR_CMP_FLAG()
	//debugging only reset_commutation_timer(MotorState.commutationTimerVal / 2);                    //reset commutation timer to 1/2 * commutation time
	MotorState.closedLoopCtrl.newComparatorCaptureDataFlag = true;
#ifndef USE_DMA_CHANNEL
	MotorState.closedLoopCtrl.newComparatorCaptureData = FTM1_C0V;
#endif
	enable_cmp_interrupt(false);

	/* debugging/testing */
	static int count = 0;
	if (debuggingBit)
	{
		Serial.println(FTM1_C0V);
		Serial.println(MotorState.closedLoopCtrl.newComparatorCaptureData);
		if (count++ >= 10)
		{
			debuggingBit = false;
			count = 0;
		}
	}
	/*******************/
	sei();
}
