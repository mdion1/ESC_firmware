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
    init_commutation_timer();
    
    while(true)
    {
        checkSPIbus();
        MotorStateTasks();
    }
    return 0;
}

void checkSPIbus()
{
    /* Check if buffer is full */
    if (SSP1STATbits.BF)
    {
        set_PWM(MotorState.closedLoopCtrl.dutyCycle = SSP1BUF);
        if (MotorState.closedLoopCtrl.dutyCycle == 0)
        {
            KILLSWITCH();
            MotorState.status = STANDBY;
        }
    }
}