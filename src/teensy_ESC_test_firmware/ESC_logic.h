#ifndef _ESC_LOGIC
#define _ESC_LOGIC

#ifdef __cplusplus
extern "C" {
#endif

#include "BAREMETAL_pins.h"

#define COMMUTATION_FILTER_SIZE 32

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
        uint32_t rollingCommutationFilter[COMMUTATION_FILTER_SIZE];
        uint8_t filterIndex;
    }closedLoopCtrl;
    /* General parameters */
    uint8_t phase;
    motorStatus_t status;
    int16_t commutationTimerVal;
}motor_state_t;

#ifdef __cplusplus
}
#endif

#endif