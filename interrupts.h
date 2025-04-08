#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <proc/ppic32mx.h>
#include <proc/p32mx564f128h.h>
#include <xc.h>
#include <sys/attribs.h>

//Set up Interrupt Controller
void setUpINTCON(void);
/*
void diINT();

void enINT(void);
 */

//############################################################################

//Set up ADC Interrupt
void setUpADCINT();

void enADCINT(void);

void diADCINT(void);

void enADCFlag(void);

void diADCFlag(void);

void __ISR(_ADC_VECTOR, IPL7SRS) ADCHandler(void);

//############################################################################

//Set Up Core Timer Interrupt
void setUpCT();

void enCT(void);

void diADC(void);

void enCTFlag(void);

void diCTFlag(void);

void __ISR(_CORE_TIMER_VECTOR, IPL4SOFT) CP0TimerHandler(void);

//############################################################################

//Set up Timer Interrupts
void setUpT1();

void enT1(void);

void diT1(void);

void enT1Flag(void);

void diT1Flag(void);

void __ISR(_TIMER_1_VECTOR, IPL4SOFT) Timer1Handler(void);

//############################################################################

void __ISR(_TIMER_2_VECTOR, IPL4SOFT) Timer2Handler(void);
void __ISR(_TIMER_3_VECTOR, IPL4SOFT) Timer3Handler(void);
void __ISR(_TIMER_4_VECTOR, IPL4SOFT) Timer4Handler(void);
void __ISR(_TIMER_5_VECTOR, IPL4SOFT) Timer5Handler(void);
void __ISR(_FAIL_SAFE_MONITOR_VECTOR, IPL4SOFT) FSMHandler(void);

#endif
