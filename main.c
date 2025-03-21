#include <xc.h>
#include "config.h"

#include "lcd.h"
#include "keypad.h"
#include "misc.h"
//#include "motor.h"0


#define KD0 LATBbits.LATB8  //pin 21
#define KD1 LATBbits.LATB9  //pin 22
#define KD2 LATBbits.LATB10 //pin 23
#define KD3 LATBbits.LATB11 //pin 24

#define KI0 PORTBbits.RB12  //pin 27
#define KI1 PORTBbits.RB13  //pin 28
#define KI2 PORTBbits.RB14  //pin 29
#define KI3 PORTBbits.RB15  //pin 30

#define DEBUG LATEbits.LATE5

void setup()
{
    
    AD1PCFG = 0x0000FF03;
    CVRCON = 0x00000200;
    DDPCON = 0x00000000;
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
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    TRISFbits.TRISF0 = 0;
    TRISFbits.TRISF1 = 0;
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    
}

int main (void) {
    setup();
    
    while (1) {
        DEBUG = 1;
        delay_us(500);
        DEBUG = 0;
        delay_us(500);
    }
    //lcd_print("Hello Akbar!", 12, 0, 0);
    
    /*
    char input = 'N';
    int position = 0;
    
    while (input != 'E') {
        input = kp_scanForInput();
        if (input == 'N' || input == 'E') {
            continue;
       } else if (input == 'D' && position > 0) {
           position -= 1;
           lcd_setDD(position);
           lcd_printChar(' ');
           lcd_setDD(position);
       } else {
           lcd_printChar(input);
           position += 1;
       }
        delay(1000000);
    }
    */
}
