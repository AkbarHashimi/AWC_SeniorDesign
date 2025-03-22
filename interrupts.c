#include <proc/ppic32mx.h>
#include <proc/p32mx564f128h.h>

/*  Set up Interrupt Controller
 * 
 */
void setUpINTCON(void){
    INTCONbits.MVEC = 0b1; // Sets Interrupts to MultiVector Mode
    
}


/*  Setup ADC Interrupt Request
 *  IRQ Number = 33; Vector Number = 27
 *  Parameters:
 *      p is an integer between 0 to 7
 *      s is an integer between 0 to 3
 */
void setUpADC(int p, int s){
    IEC1_AD1_BIT = 0b0; //Set Enable bit to 0
    IFS1_AD1_BIT = 0b0; //Set Flag bit to 0
    IPC6bits.AD1IP = p; //Set priority for ADC Interrupt
    IPC6bits.AD1IS = s; //Set sub-priority for ADC Interrupt
}


//Enable ADC Interrupt
void enADC(void){
    IEC1_AD1_BIT = 0b1;
}

//Disable ADC Interrupt
void diADC(void){
    IEC1_AD1_BIT = 0b0;
}

//Enable ADC Interrupt Flag
void enADCFlag(void){
    IFS1_AD1_BIT = 0b1; //Set Flag bit to 1
}

//Disable ADC Interrupt Flag
void diADCFlag(void){
    IFS1_AD1_BIT = 0b0; //Set Flag bit to 0
}


/*  Setup ADC Interrupt Routine
 * 
 */

/*  Setup CP0 Timer Interrupt Request
 * 
 */

/*  Setup CP0 Timer Interrupt Routine
 * 
 */

/*  Setup Timer1 Interrupt Request
 * 
 */

/*  Setup Timer1 Interrupt Routine
 * 
 */

/*  Setup Timer2 Interrupt Request
 * 
 */

/*  Setup Timer2 Interrupt Routine
 * 
 */

/*  Setup Timer3 Interrupt Request
 * 
 */

/*  Setup Timer3 Interrupt Routine
 * 
 */

/*  Setup Timer4 Interrupt Request
 * 
 */

/*  Setup Timer4 Interrupt Routine
 * 
 */

/*  Setup Timer5 Interrupt Request
 * 
 */

/*  Setup Timer5 Interrupt Routine
 * 
 */

/*  Setup Fail-Safe Clock Monitor Interrupt Request
 * 
 */

/*  Setup Fail-Safe Clock Monitor Interrupt Routine
 * 
 */
