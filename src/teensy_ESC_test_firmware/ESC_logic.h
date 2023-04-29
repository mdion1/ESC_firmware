#ifndef _ESC_LOGIC
#define _ESC_LOGIC

#include "BAREMETAL_pins.h"
#include <Arduino.h>

#define COMMUTATION_FILTER_SIZE 1

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
        uint16_t tableIndex;
    }openLoopCtrl;
    /* Closed loop control parameters */
    struct    {
        bool newComparatorCaptureDataFlag;
        bool ISR_triggered;
        int16_t newComparatorCaptureData;
        uint8_t dutyCycle;
        uint32_t rollingCommutationFilter[COMMUTATION_FILTER_SIZE];
        uint8_t filterIndex;
        uint32_t filterSum;
    }closedLoopCtrl;
    /* General parameters */
    uint8_t phase;
    motorStatus_t status;
    int16_t commutationTimerVal;
}motor_state_t;

#endif
