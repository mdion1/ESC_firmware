#include "config.h"
#include "BAREMETAL_pins.h"
#include "ESC_logic.h"

extern motor_state_t MotorState;

void checkSPIbus();

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
