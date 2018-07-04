#ifndef _ESC_LOGIC
#define _ESC_LOGIC

#include "BAREMETAL_pins.h"

typedef enum {STANDBY = 0, STARTUP, STALL, OPEN_LOOP_CTRL, CLOSED_LOOP_CTRL}motorStatus_t;

void commutate();
void MotorStateTasks();
void initMotorState();
void recalculate_commutation_time();

typedef struct 
{
    /* Open loop control parameters*/
    struct
    {
        uint8_t tableIndex;
    }openLoopCtrl;
    /* Closed loop control parameters */
    struct    {
        bool newComparatorCaptureDataFlag;
        int16_t newComparatorCaptureData;
        uint8_t dutyCycle;
    }closedLoopCtrl;
    /* General parameters */
    uint8_t phase;
    motorStatus_t status;
    int16_t commutationTimerVal;
}motor_state_t;

#endif