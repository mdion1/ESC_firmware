#ifndef _ESC_LOGIC
#define _ESC_LOGIC

#include "BAREMETAL_pins.h"

typedef enum {STANDBY = 0, STARTUP, STALL, OPEN_LOOP_CTRL, CLOSED_LOOP_CTRL}motorStatus_t;

void commutate();
void MotorStateTasks();
void initMotorState();

typedef struct 
{
    uint8_t phase/* = 0*/;
    uint8_t duty_cycle/* = 0*/;
    bool isCommutationTimerOn/* = false*/;
    bool isComparatorPhaseNext/* = false*/;
    motorStatus_t status/* = STANDBY*/;
    bool SPIdataFlag;
}motor_state_t;

#endif