#include "ESC_logic.h"

motor_state_t MotorState;

void initMotorState()
{
    MotorState.phase = 0;
    MotorState.duty_cycle = 0;
    MotorState.isCommutationTimerOn = false;
    MotorState.isComparatorPhaseNext = false;
    MotorState.status = STANDBY;
}

void MotorStateTasks()
{
    switch(MotorState.status)
    {
        case STANDBY:
            if (MotorState.duty_cycle != 0)
                MotorState.status = STARTUP;
            break;
        case STARTUP:
            break;
        case STALL:
            break;
        case OPEN_LOOP_CTRL:
            break;
        case CLOSED_LOOP_CTRL:
            break;
    }
}


#ifndef CCW_OPERATION

void commutate()
{
    switch (MotorState.phase)
    {
        /* Phase 0: Power phases A/C, B floats */
        case 0:
        {
            PHASE_A_HIGH();
            PHASE_C_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_A();
            ACMP_ASSIGN_PHASE_B();
            MotorState.phase = 1;
        }
        break;
        /* Phase 1: Power phases B/C, A floats */
        case 1:
        {
            PHASE_B_HIGH();
            PHASE_C_LOW();
            PHASE_A_TRIS();
            PWM_ASSIGN_PHASE_B();
            ACMP_ASSIGN_PHASE_A();
            MotorState.phase = 2;
        }
        break;
        /* Phase 2: Power phases B/A, C floats */
        case 2:
        {
            PHASE_B_HIGH();
            PHASE_A_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_B();
            ACMP_ASSIGN_PHASE_C();
            MotorState.phase = 3;
        }
        break;
        /* Phase 3: Power phases C/A, B floats */
        case 3:
        {
            PHASE_C_HIGH();
            PHASE_A_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_C();
            ACMP_ASSIGN_PHASE_B();
            MotorState.phase = 4;
        }
        break;
        /* Phase 4: Power phases C/B, A floats */
        case 4:
        {
            PHASE_C_HIGH();
            PHASE_A_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_C();
            ACMP_ASSIGN_PHASE_A();
            MotorState.phase = 5;
        }
        break;
        /* Phase 5: Power phases A/B, C floats */
        case 5:
        {
            PHASE_A_HIGH();
            PHASE_B_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_A();
            ACMP_ASSIGN_PHASE_C();
            MotorState.phase = 0;
        }
        break;
        default:
        break;
    }
}

#else

void commutate()
{
    switch (MotorState.phase)
    {
        /* Phase 0: Power phases A/C, B floats */
        case 0:
        {
            PHASE_A_HIGH();
            PHASE_C_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_A();
            ACMP_ASSIGN_PHASE_B();
            MotorState.phase = 5;
        }
        break;
        /* Phase 1: Power phases B/C, A floats */
        case 1:
        {
            PHASE_B_HIGH();
            PHASE_C_LOW();
            PHASE_A_TRIS();
            PWM_ASSIGN_PHASE_B();
            ACMP_ASSIGN_PHASE_A();
            MotorState.phase = 0;
        }
        break;
        /* Phase 2: Power phases B/A, C floats */
        case 2:
        {
            PHASE_B_HIGH();
            PHASE_A_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_B();
            ACMP_ASSIGN_PHASE_C();
            MotorState.phase = 1;
        }
        break;
        /* Phase 3: Power phases C/A, B floats */
        case 3:
        {
            PHASE_C_HIGH();
            PHASE_A_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_C();
            ACMP_ASSIGN_PHASE_B();
            MotorState.phase = 2;
        }
        break;
        /* Phase 4: Power phases C/B, A floats */
        case 4:
        {
            PHASE_C_HIGH();
            PHASE_A_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_C();
            ACMP_ASSIGN_PHASE_A();
            MotorState.phase = 3;
        }
        break;
        /* Phase 5: Power phases A/B, C floats */
        case 5:
        {
            PHASE_A_HIGH();
            PHASE_B_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_A();
            ACMP_ASSIGN_PHASE_C();
            MotorState.phase = 4;
        }
        break;
        default:
        break;
    }
}

#endif //#ifndef CCW_OPERATION