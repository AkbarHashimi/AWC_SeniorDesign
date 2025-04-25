#include <proc/ppic32mx.h>
#include <proc/p32mx564f128h.h>
#include <xc.h>
#include <sys/attribs.h>

/*  Set up Interrupt Controller
 * 
 */
void setUpINTCON(){
    INTCONbits.MVEC = 0b1; // Sets Interrupts to MultiVector Mode
    
}

/*Disable Interrupts globally using builtin function
 * 
 */
/*
uint32_t diINT(void){
    __builtin_disable_interrupts(void);
}
*/

/*
 * Enable Interrupts globally using builtin function
 */
/*
uint32_t enINT(void){
    __builtin_enable_interrupts(void);
}
 */


/*  Setup ADC Interrupt Request
 *  IRQ Number = 33; Vector Number = 27
 *  Set FSRSSEL to 0b111, indicating Priority 7 Interrupts will be assigned SRS
 */
void setUpADCINT(){
    IEC1bits.AD1IE = 0b0; //Set Enable bit to 0
    IFS1bits.AD1IF = 0b0; //Set Flag bit to 0
    IPC6bits.AD1IP = 7; //Set priority for ADC Interrupt to 7
    IPC6bits.AD1IS = 0; //Set sub-priority for ADC Interrupt to 0
}


//Enable ADC Interrupt
void enADCINT(){
    IEC1bits.AD1IE = 0b1;
}

//Disable ADC Interrupt
void diADCINT(){
    IEC1bits.AD1IE = 0b0;
}

//Enable ADC Interrupt Flag
void enADCFlag(){
    IFS1bits.AD1IF = 0b1; //Set Flag bit to 1
}

//Disable ADC Interrupt Flag
void diADCFlag(){
    IFS1bits.AD1IF = 0b0; //Set Flag bit to 0
}

//###########################################################################

/*  Setup Core Timer Interrupt
 *  IRQ Number = 0; Vector Number = 0
 *  Set FSRSSEL to 0b111, indicating Priority 7 Interrupts will be assigned SRS
 */
void setUpCT(){
    IEC0bits.CTIE = 0b0; //Set Enable bit to 0
    IFS0bits.CTIF= 0b0; //Set Flag bit to 0
    IPC0bits.CTIP = 5; //Set priority for ADC Interrupt to 7
    IPC0bits.CTIS = 0; //Set sub-priority for ADC Interrupt to 0
}

//Enable CT Interrupt
void enCT(){
    IEC0bits.CTIE = 0b1;
}

//Disable CT Interrupt
void diADC(){
    IEC0bits.CTIE = 0b0;
}

//Enable CT Interrupt Flag
void enCTFlag(){
    IFS0bits.CTIF = 0b1; //Set Flag bit to 1
}

//Disable CT Interrupt Flag
void diCTFlag(){
    IFS0bits.CTIF = 0b0; //Set Flag bit to 0
}

/*  CP0 Timer Interrupt Routine
 * 
 */
void __ISR(_CORE_TIMER_VECTOR, IPL4SOFT) CP0TimerHandler(){
    //Do something
    
    //Clear the flag
    diCTFlag();
}

//###########################################################################

/*  Setup Timer1 Interrupt
 *  IRQ Number = 4; Vector Number = 4
 *  Set FSRSSEL to 0b111, indicating Priority 7 Interrupts will be assigned SRS
 */
void setUpT1(){
    IEC0bits.T1IE = 0b0; //Set Enable bit to 0
    IFS0bits.T1IF = 0b0; //Set Flag bit to 0
    IPC1bits.T1IP = 5; //Set priority for T1 Interrupt to 5
    IPC1bits.T1IS = 0; //Set sub-priority for T1 Interrupt to 0
}

//Enable T1 Interrupt
void enT1(void){
    IEC0bits.T1IE  = 0b1;
}

//Disable TMR1 Interrupt
void diT1(void){
    IEC0bits.T1IE  = 0b0;
}

//Enable TMR1 Interrupt Flag
void enT1Flag(void){
    IFS0bits.T1IF  = 0b1; //Set Flag bit to 1
}

//Disable TMR1 Interrupt Flag
void diT1Flag(void){
    IFS0bits.T1IF  = 0b0; //Set Flag bit to 0
}

//###########################################################################

/*  Timer2 Interrupt Service Routine
 * 
 */
void __ISR(_TIMER_2_VECTOR, IPL4SOFT) Timer2Handler(){
    //Do something
    
    //Clear the flag
    
}

/*  Timer3 Interrupt Service Routine
 * 
 */
void __ISR(_TIMER_3_VECTOR, IPL4SOFT) Timer3Handler(){
    //Do something
    
    //Clear the flag
    
}

/*  Setup Timer4 Interrupt Service Routine
 * 
 */
void __ISR(_TIMER_4_VECTOR, IPL4SOFT) Timer4Handler(){
    //Do something
    
    //Clear the flag
    
}

/*  Setup Timer5 Interrupt Service Routine
 * 
 */
void __ISR(_TIMER_5_VECTOR, IPL4SOFT) Timer5Handler(){
    //Do something
    
    //Clear the flag
    
}

/*  Fail-Safe Clock Monitor Interrupt Service Routine
 * 
 */
void __ISR(_FAIL_SAFE_MONITOR_VECTOR, IPL4SOFT) FSMHandler(){
    //Do something
    
    //Clear the flag
    
}
