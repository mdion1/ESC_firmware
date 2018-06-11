#ifndef _BAREMETAL_PINS_H
#define _BAREMETAL_PINS_H

#include <pic16f18346.h>
#include <stdint.h>
#include <stdbool.h>
#include "Motor_direction.h"

/****************** MCU pinout ******************/
/*
Motor commutation pins
A_hi/lo = A4
A_on/off = A5
B_hi/lo = B4
B_on/off = B6
C_hi/lo = C5
C_on/off = C7

BEMF sensing pins
In_Vbatt = C0
In_A = C1
In_B = C2
In_C = C3

Slave SPI pins
SCK = B7
MOSI = B5
SS = C6

*/

#define PHASE_A_HIGH() PORTA |= 1 << 4;
#define PHASE_A_LOW()  PORTA &= ~(1 << 4); PORTA |= 1 << 5;
#define PHASE_A_TRIS() PORTA &= ~(1 << 5);
#define PHASE_B_HIGH() PORTB |= 1 << 4;
#define PHASE_B_LOW()  PORTB &= ~(1 << 4); PORTB |= 1 << 6;
#define PHASE_B_TRIS() PORTB &= ~(1 << 6);
#define PHASE_C_HIGH() PORTC |= 1 << 5;
#define PHASE_C_LOW()  PORTC &= ~(1 << 5); PORTC |= 1 << 7;
#define PHASE_C_TRIS() PORTC &= ~(1 << 7);
#define PWM_ASSIGN_PHASE_A() RA5PPS = 0b01100; RB6PPS = RC7PPS = 0;
#define PWM_ASSIGN_PHASE_B() RB6PPS = 0b01100; RA5PPS = RC7PPS = 0;
#define PWM_ASSIGN_PHASE_C() RC7PPS = 0b01100; RA5PPS = RB6PPS = 0;
#define ACMP_ASSIGN_PHASE_A() CM2CON1bits.C2NCH = 1;
#define ACMP_ASSIGN_PHASE_B() CM2CON1bits.C2NCH = 2;
#define ACMP_ASSIGN_PHASE_C() CM2CON1bits.C2NCH = 3;
#define KILLSWITCH() PORTA = PORTB = PORTC = 0;

typedef enum {TIMER_DIV_1 = 0, TIMER_DIV_2, TIMER_DIV_4, TIMER_DIV_8}timer_div_t;

void init_pins();
void init_commutation_timer(int16_t period, timer_div_t div);
void start_commutation_timer(bool on);
void init_event_timer();
bool check_event_timer_overflow();
void init_PWM();
void init_comparator();
void enable_cmp_interrupt(bool on);
void init_spi();

#endif