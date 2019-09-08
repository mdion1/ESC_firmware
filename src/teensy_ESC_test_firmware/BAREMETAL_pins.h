#ifndef _BAREMETAL_PINS_H
#define _BAREMETAL_PINS_H

#include <stdint.h>
#include <stdbool.h>
#include "Motor_direction.h"
#include <Arduino.h>
#include "DMAreg.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************** MCU pinout ******************/
/*
Motor commutation pins
A_hi/lo = B16 (Teensy pin 0)
A_on/off = C1 (Teensy pin 22)
B_hi/lo = B17 (Teensy pin 1)
B_on/off = C2 (Teensy pin 23)
C_hi/lo = D0 (Teensy pin 2)
C_on/off = C3 (Teensy pin 9)

BEMF sensing pins
In_Vbatt = C6 (Teensy pin 11)
In_A = C7 (Teensy pin 12)
In_B = C8 (Teensy pin 28)
In_C = C9 (Teensy pin 27)
CMP out = C5 (Teensy pin 13)

*/

/* PWM output manipulation */
#define PWM_ASSIGN_PHASE_A()    PORTC_PCR1 = 4 << 8;  \
								PORTC_PCR2 = 1 << 8;  \
								PORTC_PCR3 = 1 << 8;      //(1) Assigns FTM0_CH0 output; (2) Assigns GPIO function; (3) Assigns GPIO function;
						
#define PWM_ASSIGN_PHASE_B()    PORTC_PCR1 = 1 << 8;  \
								PORTC_PCR2 = 4 << 8;  \
								PORTC_PCR3 = 1 << 8;     //(1) Assigns GPIO function; (2) Assigns FTM0_CH1 output; (3) Assigns GPIO function;
						
#define PWM_ASSIGN_PHASE_C()    PORTC_PCR1 = 1 << 8;  \
								PORTC_PCR2 = 1 << 8;  \
								PORTC_PCR3 = 4 << 8;     //(1) Assigns GPIO function; (2) Assigns GPIO function; (3) Assigns FTM0_CH2 output;
						
/* Gate driver pins */
#define PHASE_A_HIGH()    GPIOC_PSOR = 1 << 1; GPIOB_PSOR = 1 << 16;
#define PHASE_A_LOW()     GPIOC_PSOR = 1 << 1; GPIOB_PCOR = 1 << 16;
#define PHASE_A_TRIS()    GPIOC_PCOR = 1 << 1;
#define PHASE_B_HIGH()    GPIOC_PSOR = 1 << 2; GPIOB_PSOR = 1 << 17;
#define PHASE_B_LOW()     GPIOC_PSOR = 1 << 2; GPIOB_PCOR = 1 << 17;
#define PHASE_B_TRIS()    GPIOC_PCOR = 1 << 2;
#define PHASE_C_HIGH()    GPIOC_PSOR = 1 << 3; GPIOD_PSOR = 1 << 0;
#define PHASE_C_LOW()     GPIOC_PSOR = 1 << 3; GPIOD_PCOR = 1 << 0;
#define PHASE_C_TRIS()    GPIOC_PCOR = 1 << 3;
#define KILLSWITCH() GPIOC_PCOR = (1 << 3) | (1 << 2) | (1 << 1);

/* Comparator module GPIO manipulation */
#define ACMP_ASSIGN_PHASE_A() CMP0_MUXCR = 1 << 0;
#define ACMP_ASSIGN_PHASE_B() CMP0_MUXCR = 2 << 0;
#define ACMP_ASSIGN_PHASE_C() CMP0_MUXCR = 3 << 0;
#define CLEAR_CMP_FLAG()	CMP0_SCR |= 1 << 2;		//clear interrupt flag by writing a 1; Bit 2 = CFR, comparator flag rising

/* commutation timer (FTM1) */
#define CLEAR_COMMUTATION_TMR_OVF_FLAG() FTM1_SC &= ~(1 << 7);		//clear overflow interrupt flag (TOF = bit 7)


void init_pins();
void init_commutation_timer();
void reset_commutation_timer(int16_t val);
void start_commutation_timer(bool on);
void init_event_timer();
bool check_event_timer_overflow();
void init_PWM();
void set_PWM(uint8_t val);
void init_comparator();
void enable_cmp_interrupt(bool on);

#ifdef __cplusplus
}
#endif

#endif
