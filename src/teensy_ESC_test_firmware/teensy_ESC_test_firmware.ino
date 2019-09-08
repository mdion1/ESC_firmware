#include "BAREMETAL_pins.h"

bool debuggingBit = false;

void setup()
{
    Serial.begin(9600);
    init_pins();
    init_PWM();
	set_PWM(64);
    PWM_ASSIGN_PHASE_A()
    init_comparator();
    ACMP_ASSIGN_PHASE_A()
    //initMotorState();
    //init_event_timer();
    init_commutation_timer();
	reset_commutation_timer(-16384);
	start_commutation_timer(true);
	sei();
}

void loop()
{
  checkSerial();
  //MotorStateTasks();
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
        Serial.println(CMP0_CR1);
      }
      break;
      case 'b':
		debuggingBit = true;
      break;
      default:
      break;
    }
  }
}
