#include "BAREMETAL_pins.h"
#include "ESC_logic.h"

bool debuggingBit = false;
extern motor_state_t MotorState;

void setup()
{
    Serial.begin(9600);
    init_pins();
    init_PWM();
    init_comparator();
    initMotorState();
    init_commutation_timer();
	  sei();
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
      break;
      case '1':
      {
        set_PWM(MotorState.closedLoopCtrl.dutyCycle = 40);
        init_event_timer();
      }
      break;
      case '0':
      {
        set_PWM(MotorState.closedLoopCtrl.dutyCycle = 0);
        KILLSWITCH();
        MotorState.status = STANDBY;
      }
      break;
      default:
      break;
    }
  }
}
