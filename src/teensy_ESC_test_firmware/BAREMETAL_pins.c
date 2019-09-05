#include "BAREMETAL_pins.h"
#include "ESC_logic.h"

extern motor_state_t MotorState;
extern uint16_t OpenLoopCommutationTable[256];
const int16_t PWM_initial_timer_val = 0xff00;   //timer overflows after 256 counts

void init_pins()
{
    /* set output pins */
    GPIOB_PDDR |= (1 << 16);    //Teensy pin 0 (B16) = A_hi/lo
    GPIOB_PDDR |= (1 << 17);    //Teensy pin 1 (B17) = B_hi/lo
    GPIOD_PDDR |= (1 << 0);     //Teensy pin 2 (D0) = C_hi/lo
    GPIOC_PDDR |= (1 << 1);     //Teensy pin 22 (C1) = A_on/off
    GPIOC_PDDR |= (1 << 2);     //Teensy pin 23 (C2) = B_on/off
    GPIOC_PDDR |= (1 << 3);     //Teensy pin 9 (C3) = C_on/off
    GPIOC_PDDR |= (1 << 6);     //Teensy pin 11 (C6) = CMP0_out
}

void init_commutation_timer()
{
    /* Flex Timer 2, channel 0, input capture mode setup */
    FTM2_C0SC |= 1 << 2;                                      // ESLnB:ELSEnA(3:2) = 01 for input capture on rising edge
    SIM_SOPT4 |= 1 << 20;                                     //set FTM2CH0SRC (input capture source, bits 21:20) to CMP0_OUT
}

void reset_commutation_timer(int16_t val)
{
    FTM2_CNTIN = (uint16_t)(-val);
    FTM2_CNT = FTM2_CNTIN;
}

void start_commutation_timer(bool on)
{
    FTM2_SC = 1 << 3;           //select system clock, enabling module
    FTM2_SC |= 1 << 6;          //enable overflow interrupt (TOIE = bit 6)
    
}

void init_event_timer()
{
	//todo
    //T4CONbits.T4OUTPS = 4;      // 1:5 postscaler
    //T4CONbits.T4CKPS = 3;       // 1:64 prescaler
    //T4CONbits.TMR4ON = 1;       //  ==> ~100Hz clock
}

bool check_event_timer_overflow()
{
	//todo
    //if (PIR2bits.TMR4IF)
    //{
    //    PIR2bits.TMR4IF = 0;
    //    return true;
    //}
    return false;
}

void init_PWM()
{
    /* PWM setup */
    FTM0_SC = 1 << 3;                                 //select system clock, enabling module
    FTM0_C0SC = (1 << 5) | (1 << 3);                  //select edge-aligned PWM, MSB:MSA = 10, ELSB:ELSA = 10
    FTM0_C1SC = FTM0_C2SC = FTM0_C0SC;
    FTM0_CNTIN = 0;
    FTM0_MOD = 255;
    FTM0_C0V = FTM0_C1V = FTM0_C2V = 32;              //start with an initial duty cycle of 1/8
}

void set_PWM(uint8_t val)
{
	//todo
    //CCPR1H = (uint16_t)(val + PWM_initial_timer_val);
}

void init_comparator()
{
  /* Comparator module CMP0 */
    SIM_SCGC4 |= 1 << 19;                                     //enable comparoator clock gate control
    CMP0_CR1 |= (1 << 4) | (1 << 1) | (1 << 0);               //high-power mode; output pin enable; module enable
    PORTC_PCR6 = PORTC_PCR7 = PORTC_PCR8 = PORTC_PCR9 = 0;    //Assign (default) comparator input pins
    PORTC_PCR5 = 6 << 8;                                      //assign CMP0_OUT to Teensy pin 13 (port C5)
}

void enable_cmp_interrupt(bool on)
{
	//todo
    //PIR2bits.C2IF = 0;  //clear flag
    //PIE2bits.C2IE = on;
}

void blank(uint8_t val)
{
	//todo
//    if (!T1CONbits.TMR1ON)
//        return;
//    
//#define NOW ((TMR1H << 8) | TMR1L)
//    uint16_t start = NOW;
//    while (NOW - start < val)
//    {
//        asm("NOP");
//    }
}
