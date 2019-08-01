#include "BAREMETAL_pins.h"
#include "ESC_logic.h"

extern motor_state_t MotorState;
extern uint16_t OpenLoopCommutationTable[256];

void init_pins()
{
    /* set output pins */
    PORTA = PORTB = PORTC = 0;
    TRISAbits.TRISA4 = 0;       //phase A hi/lo
    TRISAbits.TRISA5 = 0;       //phase A on/off
    TRISBbits.TRISB4 = 0;       //phase B hi/lo
    TRISBbits.TRISB6 = 0;       //phase B on/off
    TRISCbits.TRISC5 = 0;       //phase C hi/lo
    TRISCbits.TRISC7 = 0;       //phase C on/off
    TRISAbits.TRISA2 = 0;   //unused pin
    TRISCbits.TRISC4 = 0;   //unused pin
    
    /* set analog input pins */
    ANSELC |= (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
    
    /* enable interrupts */
    INTCONbits.GIE = 1;     //global interrupt enable
    INTCONbits.PEIE = 1;    //enables active peripheral interrupts
}

void init_commutation_timer()
{
    T1CONbits.T1CKPS = 1;
}

void reset_commutation_timer(int16_t val)
{
    TMR1L = (uint8_t) val;
    TMR1H = (uint8_t) (val >> 8);
}

void start_commutation_timer(bool on)
{
    T1CONbits.TMR1ON = on;      // enable timer
    PIE1bits.TMR1IE = on;       // enable overflow interrupt
}

void init_event_timer()
{
    T4CONbits.T4OUTPS = 4;      // 1:5 postscaler
    T4CONbits.T4CKPS = 3;       // 1:64 prescaler
    T4CONbits.TMR4ON = 1;       //  ==> ~100Hz clock
}

bool check_event_timer_overflow()
{
    if (PIR2bits.TMR4IF)
    {
        PIR2bits.TMR4IF = 0;
        return true;
    }
    return false;
}

void init_PWM()
{
    /* Configure CCP (capture-compare-PWM) registers */
    CCP1CONbits.CCP1EN = 1;             //enable CCP module
    CCP1CONbits.CCP1FMT = 1;            //left-aligned 10-bit PWM word
    CCP1CONbits.CCP1MODE = 0b1111;      //enable PWM mode
    CCPTMRSbits.C1TSEL = 0b00;          //select Timer2 as clock source
    CCPR1L = 0;                         //clear the two LSB's of the PWM word (only 8 bits used)
    CCPR1H = 48;                         //start with a duty cycle of 0;
    
    /* Configure Timer2 */
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2OUTPS = 0;
    PR2 = 255;
}

void set_PWM(uint8_t val)
{
    CCPR1H = val;
}

void init_comparator()
{
    CM2CON0bits.C2ON = 1;    //enable comparator
    CM2CON0bits.C2SYNC = 1;    //sync Timer1 with comparator (output updated on the falling edge of Timer1 clock source
    CM2CON1bits.C2PCH = 0;    //set positive input
    CM2CON1bits.C2INTN = 1;   //enable interrupt on falling edge
    
    /* debugging only: enable comparator output at C4 (pin 6) */
    RC4PPS = 0b10111;
    ANSELCbits.ANSC4 = 0;
    TRISCbits.TRISC4 = 0;
    
    /* debugging alternate: A2 (pin 17) */
    //RA2PPS = 0b10111;
    //ANSELAbits.ANSA2 = 0;
    //TRISAbits.TRISA2 = 0;
}

void enable_cmp_interrupt(bool on)
{
    PIR2bits.C2IF = 0;  //clear flag
    PIE2bits.C2IE = on;
}

void init_spi()
{
    /* assign pins */
    SSP1CLKPPS = 0b01111;   //assign SCK input to B7
    SSP1DATPPS = 0b01101;   //assign SDI input to B5
    SSP1SSPPS =  0b10110;   //assign ~SS input to C6
    
    ANSELBbits.ANSB7 = 0;
    ANSELBbits.ANSB5 = 0;
    ANSELCbits.ANSC6 = 0;

    /* configure registers */
    SSP1STATbits.SMP = 0;    //must be cleared for slave mode
    SSP1STATbits.CKE = 1;    //SPI mode 0 (errata, CKE setting is incorrect)
    SSP1CON1bits.SSPEN = 1;  //enable SPI mode
    SSP1CON1bits.CKP = 0;    //SPI mode 0
    SSP1CON1bits.SSPM = 0b0100;    //SPI slave mode, clock = SCK pin, ~SS pin control enabled
    SSP1CON3bits.BOEN = 1;    //Buffer overwrite enable bit set
}

void blank(uint8_t val)
{
    if (!T1CONbits.TMR1ON)
        return;
    
#define NOW ((TMR1H << 8) | TMR1L)
    uint16_t start = NOW;
    while (NOW - start < val)
    {
        asm("NOP");
    }
}