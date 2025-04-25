#include <xc.h>
#include "config.h"

#include "lcd.h"
#include "keypad.h"
#include "misc.h"
#include "motor.h"
#include "timers.h"
#include "adc.h"
#include "interrupts.h"


#define KD0 LATBbits.LATB8  //pin 21
#define KD1 LATBbits.LATB9  //pin 22
#define KD2 LATBbits.LATB10 //pin 23
#define KD3 LATBbits.LATB11 //pin 24

#define KI0 PORTBbits.RB12  //pin 27
#define KI1 PORTBbits.RB13  //pin 28
#define KI2 PORTBbits.RB14  //pin 29
#define KI3 PORTBbits.RB15  //pin 30

#define DEBUG LATEbits.LATE5

 

/*  ADC Interrupt Service Routine
 *      ADC first reads the buffer, then clears the flag
 */
void __ISR(_ADC_VECTOR, IPL7SRS) ADCHandler(){
    __builtin_disable_interrupts();
    //Do some things
    LATEINV = 0b100000;        //Invert Debug LED
    
    int n = 5000000;              //Delay for a short period
    while(n > 0){
        n--;
    }
    
    //Read the buffer
    n = ADC1BUF2;
    n = ADC1BUF3;
    
    //Clear the flag
    diADCFlag(); 
    __builtin_enable_interrupts();
}


/*  Timer1 Interrupt Service Routine
 * 
 */
void __ISR(_TIMER_1_VECTOR, IPL5SOFT) Timer1Handler(){
        //Do some things
    //__builtin_disable_interrupts();
    LATEbits.LATE5 = 0b1;        //Turn Debug LED on
    
    TMR1 = 0x0000;
    
    //Clear the flag
    IFS0bits.T1IF  = 0b0;
    //__builtin_enable_interrupts();
}

void setup()
{
    
    AD1PCFG = 0x0000FF03;
    CVRCON = 0x00000200;
    DDPCON = 0x00000000;
    OSCCONCLR = 0xFFFFFFFF;
    //0 == output
    //1 == input
    
    //set keypad driving pins to output:
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB11 = 0;
    //set keypad input pins to input:
    TRISBbits.TRISB12 = 1;
    TRISBbits.TRISB13 = 1;
    TRISBbits.TRISB14 = 1;
    TRISBbits.TRISB15 = 1;
    
    //Set Debug LED
    TRISEbits.TRISE5 = 0;
    
    //keypad drivers:
    LATBbits.LATB8 = 0;
    LATBbits.LATB9 = 0;
    LATBbits.LATB10 = 0;
    LATBbits.LATB11 = 0;
    
    //keypad inputs:
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 0;
    
    //LCD pins:
    TRISDbits.TRISD0 = 0;
    TRISCbits.TRISC13 = 0;
    TRISCbits.TRISC14 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    TRISFbits.TRISF0 = 0;
    
    // motor pins:
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;
    TRISEbits.TRISE4 = 0;
    
}

void loop() {
    char input = 'N';
    int steps = 0;
    
    int position = 0;
    
    lcd_clear();
    lcd_print("Enter steps:", 12, 0, 0);
    
    lcd_setDD(0x40);
    
    while (input != 'E') {
        input = kp_scanForInput();
        
        if (input == 'N') {
            // nothing found
            continue;
        }
        
        // if valid button pushed, store result
        steps = misc_modifyTotal(steps, input);
        
        // if we are deleting
        if (input == 'D' && position > 0) {
            position--;
            lcd_setDD(0x40 + position);
            lcd_printChar(' ');
            lcd_setDD(0x40 + position);
        } else if (input != 'E' && input != 'D') {
            // if this is new number
            position++;
            lcd_printChar(input);
        }
         delay_ms(500);
    }
    PS = 1; // enable motors
    delay_us(20);
    // for demonstration, step motor # of steps
    motor_stepFeeder(steps);
    motor_cut();
    PS = 0; //disable motors
}

int main (void) {
    setup();

    
    //adc_init();
    
    lcd_init();
    PS = 0;
    

    adc_init();
    adc_on();
    
     
    INTCONbits.MVEC = 0b1;  // Sets Interrupts to MultiVector Mode
    //Set Up ADC Interrupt
    IEC1bits.AD1IE = 0b0;   //Set Enable bit to 0
    IFS1bits.AD1IF = 0b0;   //Set Flag bit to 0
    IPC6bits.AD1IP = 7;     //Set priority for ADC Interrupt to 7
    IPC6bits.AD1IS = 0;     //Set sub-priority for ADC Interrupt to 0
    IEC1bits.AD1IE = 0b1;   //Enable ADC Interrupt
    
    //Set Up T1 Interrupt
    IEC0bits.T1IE = 0b0;    //Set Enable bit to 0
    IFS0bits.T1IF = 0b0;    //Set Flag bit to 0
    IPC1bits.T1IP = 5;      //Set priority for T1 Interrupt to 5
    IPC1bits.T1IS = 0;      //Set sub-priority for T1 Interrupt to 0
    
    //IEC0bits.T1IE  = 0b1;   //Enable T1 Interrupt
    setTimer1(50000);
    __builtin_enable_interrupts();
    
   
    
    //lcd_init();
    
    //lcd_clear();
    
    int n = 0;
    
    //TRISEbits.TRISE5 = 0b0;
    LATEbits.LATE5 = 0b0;   //Turn Debug LED off
    
    while (1) {      
        if(n == 0)
                n = 5000;
        else
            n--;
    }
    
}
