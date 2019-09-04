void setup()
{
    init_pins();
    init_PWM();
    //init_comparator();
    //initMotorState();
    //init_event_timer();
    //init_commutation_timer();
}

void loop()
{
  checkSerial();
  MotorStateTasks();
}
