#include "BAREMETAL_pins.h"
#include "ESC_logic.h"
#include <Arduino.h>

extern motor_state_t MotorState;
extern bool debuggingBit;

/* Flex timer 1 (commutation timer) overflow interrupt ISR */
void ftm1_isr(void) {
	cli();
	CLEAR_COMMUTATION_TMR_OVF_FLAG()
  commutate();
  bool Comparator_trig_missed = false;
  if (MotorState.status == CLOSED_LOOP_CTRL && !(MotorState.phase & 1))
  {
    if (MotorState.closedLoopCtrl.ISR_triggered)
    {
      MotorState.closedLoopCtrl.ISR_triggered = false;
    }
    else
      Comparator_trig_missed = true;
  }
  reset_commutation_timer(MotorState.commutationTimerVal);

  if (Comparator_trig_missed)
  {
    MotorState.closedLoopCtrl.newComparatorCaptureDataFlag = true;
    MotorState.closedLoopCtrl.newComparatorCaptureData = MotorState.commutationTimerVal;
  }
	

    /*if (debuggingBit && MotorState.status == CLOSED_LOOP_CTRL)
    {
      
      static int count = 0;
      if (count < 300)
        count++;
      else
      {
        Serial.println("debugging bit off");
        debuggingBit = false;
        count = 0;
      }
      if (count % 2)
        Serial.println(MotorState.commutationTimerVal);
      if (Comparator_trig_missed)
        Serial.println("trig missed");
    }*/
  
	sei();
}

void cmp0_isr(void) {
	cli();
  
	CLEAR_CMP_FLAG()
	//debugging only reset_commutation_timer(MotorState.commutationTimerVal / 2);                    //reset commutation timer to 1/2 * commutation time
  MotorState.closedLoopCtrl.ISR_triggered = true;
	MotorState.closedLoopCtrl.newComparatorCaptureDataFlag = true;
	MotorState.closedLoopCtrl.newComparatorCaptureData = FTM1_C0V;
	enable_cmp_interrupt(false);
  
	sei();
}
