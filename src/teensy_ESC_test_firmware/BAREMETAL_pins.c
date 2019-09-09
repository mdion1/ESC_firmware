#include "BAREMETAL_pins.h"
#include "ESC_logic.h"
#include <Arduino.h>

extern motor_state_t MotorState;
static uint32_t lastEvent;

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
    /* Flex Timer 1, channel 0, input capture mode setup */
	FTM1_SC |= 1 << 3;           //select system clock, enabling module
	FTM1_SC |= 2 << 0;			 //Prescaler = 4:1
    FTM1_C0SC = 1 << 2;                                      // ESLnB:ELSEnA(3:2) = 01 for input capture on rising edge
    SIM_SOPT4 |= 1 << 18;                                     //set FTM1CH0SRC (input capture source, bits 19:18) to CMP0_OUT
	FTM1_CNTIN = 0;
 NVIC_ENABLE_IRQ(IRQ_FTM1);
}

void reset_commutation_timer(int16_t val)
{
	FTM1_MOD = val;
    FTM1_CNT = 0;			//any write to FTMx_CNT resets value to FTMx_CNTIN
}

void start_commutation_timer(bool on)
{
	if (on)
	{
		CLEAR_COMMUTATION_TMR_OVF_FLAG()
		FTM1_SC |= 1 << 6;          //enable overflow interrupt (TOIE = bit 6)
	}
	else
		FTM1_SC &= ~(1 << 6);       //disable overflow interrupt
}

void init_event_timer()
{
	lastEvent = millis();
}

bool check_event_timer_overflow()
{
	if (millis() - lastEvent >= 100)
	{
		lastEvent += 100;
		return true;
	}
	else
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
    FTM0_C0V = FTM0_C1V = FTM0_C2V = 0;              //start with an initial duty cycle of 0
}

void set_PWM(uint8_t val)
{
	FTM0_C0V = FTM0_C1V = FTM0_C2V = val;
}

void init_comparator()
{
  /* Comparator module CMP0 */
    SIM_SCGC4 |= 1 << 19;                                     //enable comparoator clock gate control
    CMP0_CR1 |= (1 << 4) | (1 << 1) | (1 << 0);               //high-power mode; output pin enable; module enable
    PORTC_PCR6 = PORTC_PCR7 = PORTC_PCR8 = PORTC_PCR9 = 0;    //Assign (default) comparator input pins
    PORTC_PCR5 = 6 << 8;                                      //assign CMP0_OUT to Teensy pin 13 (port C5)
    NVIC_ENABLE_IRQ(IRQ_CMP0);

#ifdef USE_DMA_CHANNEL
	/* DMA transfer setup */
	SIM_SCGC7 |= SIM_SCGC7_DMA;                             //enables clock gate to DMA module
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX;                          //enables clock gate to DMA Mux module
	CMP0_SCR |= 1 << 6;										//(bit 6 = DMAEN, DMA enable)
	TCD_t * mTCD = &DMA_TCD0_SADD;
	mTCD->SADDR = &FTM1_C0V;									//commutation timer count reg = DMA tranfser source
	mTCD->SOFF = 0;											//source address does not increment
	mTCD->ATTR_SRC = DMA_TCD_ATTR_SIZE_16BIT;
	mTCD->ATTR_DST = DMA_TCD_ATTR_SIZE_16BIT;
	mTCD->NBYTES_MLNO = mTCD->NBYTES_MLNO = 2;				//2 bytes per minor loop
	mTCD->SLAST = 0;
	mTCD->DADDR = &MotorState.closedLoopCtrl.newComparatorCaptureData;	//DMA transfer destination
	mTCD->DOFF = 0;											//destination address does not increment
	mTCD->DLASTSGA = 0;
	mTCD->BITER = mTCD->CITER = 0;
	mTCD->CSR = 0;

	DMAMUX_CHCFG0 = (1 << 7) | (42 << 0);					//enables DMA ch0, specifies CMP0 as trigger source
	DMA_ERQ |= 1 << 0;                                      //enable request register
#endif
}

void enable_cmp_interrupt(bool on)
{
	if (on)
	{
		CLEAR_CMP_FLAG()
		CMP0_SCR |= 1 << 4;			//(bit 4 = IER, interrupt enable rising)
	}
	else
		CMP0_SCR &= ~(1 << 4);
}
