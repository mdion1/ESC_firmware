#include "BAREMETAL_pins.h"
#include "ESC_logic.h"
#include "filter.h"

bool debuggingBit = false;
extern motor_state_t MotorState;
filter * mFilt;

void setup()
{
    Serial.begin(9600);
    init_pins();
    init_PWM();
    init_comparator();
    initMotorState();
    init_commutation_timer();
	  sei();
    mFilt = new filter(4);
}

void loop()
{
  checkSerial();
  MotorStateTasks();
}

void checkSerial()
{
  if (Serial.available())
  {
    switch (Serial.read())
    {
      case 'a':
      {
        Serial.println("hello");
      }
      break;
      case 'b':
		debuggingBit = true;
    Serial.println("debugging bit on");
      break;
      case '2':
      {
        MotorState.status = CLOSED_LOOP_CTRL;
        enable_cmp_interrupt(true);
        DEBUG_PIN_14_HIGH()
      }
      break;
      case '1':
      {
        set_PWM(MotorState.closedLoopCtrl.dutyCycle = 50);
        init_event_timer();
      }
      break;
      case '0':
      {
        set_PWM(MotorState.closedLoopCtrl.dutyCycle = 0);
        KILLSWITCH();
        initMotorState();
        MotorState.status = STANDBY;
        DEBUG_PIN_14_LOW()
      }
      break;
      case '+':
      {
        set_PWM(++MotorState.closedLoopCtrl.dutyCycle);
        Serial.println(MotorState.closedLoopCtrl.dutyCycle);
      }
      break;
      case '-':
      {
        set_PWM(--MotorState.closedLoopCtrl.dutyCycle);
        Serial.println(MotorState.closedLoopCtrl.dutyCycle);
      }
      break;
      default:
      break;
    }
  }
}
