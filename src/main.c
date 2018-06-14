#include "config.h"
#include "BAREMETAL_pins.h"
#include "ESC_logic.h"

extern motor_state_t MotorState;

void checkSPIbus();

int main()
{
    init_pins();
    init_spi();
    init_PWM();
    init_comparator();
    initMotorState();
    init_event_timer();   
    
    while(true)
    {
        checkSPIbus();
        if (check_event_timer_overflow())
            MotorStateTasks();
    }
    return 0;
}

void checkSPIbus()
{
    /* Check if buffer is full */
    if (SSP1STATbits.BF)
    {
        MotorState.duty_cycle = SSP1BUF;
        if (MotorState.duty_cycle == 0)
        {
            KILLSWITCH();
            MotorState.status = STANDBY;
        }
        MotorState.SPIdataFlag = true;
    }
}