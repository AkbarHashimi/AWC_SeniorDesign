#include "lcd.h"
#include "misc.h"
#include <xc.h>

char kp_getSymbol(int row, int column) { 
    //converts a row and column into the corresponding character on the keypad
    
    //e.g. hitting the top left button (row 0 column 0)
    //should return the character '1'
    
    LATBbits.LATB8 = 0; //turn off all driving pins so no mistaken inputs upon loop
    LATBbits.LATB9 = 0;
    LATBbits.LATB10 = 0;
    LATBbits.LATB11 = 0;

	switch (row) {
		case 0:
			switch (column) {
				case 0:	return '1';
				case 1: return '2';
				case 2: return '3';
				case 3: return 'N'; //do nothing
			}
		case 1:
			switch (column) {
				case 0:	return '4';
				case 1: return '5';
				case 2: return '6';
				case 3: return 'N'; //do nothing
			}
		case 2:
			switch (column) {
				case 0:	return '7';
				case 1: return '8';
				case 2: return '9';
				case 3: return 'D'; //delete
			}
		case 3:
			switch (column) {
				case 0:	return 'N'; //do nothing
				case 1: return '0';
				case 2: return 'N'; //do nothing
				case 3: return 'E'; //enter
			}
	}	
    return 'N';
}

char kp_scanForInput() {
    
    //loop across every keypad input port to test for connection
    //connection established when button is pressed
    //row and column of button press is determined as we loop
    //the corresponding character is returned from getSymbol()
    
    //keypad drive pins start at RB8
    //keypad-in bits start at RB12 
	LATBbits.LATB8 = 1;
    //turn on keypad driving pin		
    if (PORTBbits.RB12 == 1) {          //check each keypad input for connection
        return kp_getSymbol(3, 3);
    } else if (PORTBbits.RB13 == 1) {
        return kp_getSymbol(2, 3);
    } else if (PORTBbits.RB14 == 1) {
        return kp_getSymbol(1, 3);
    } else if (PORTBbits.RB15 == 1) {
        return kp_getSymbol(0, 3);
    }
    LATBbits.LATB8 = 0;                 //turn off keypad drive
   
    
    LATBbits.LATB9 = 1;
    if (PORTBbits.RB12 == 1) {                                         
        return kp_getSymbol(3, 2);
    } else if (PORTBbits.RB13 == 1) {
        return kp_getSymbol(2, 2);
    } else if (PORTBbits.RB14 == 1) {
        return kp_getSymbol(1, 2);
    } else if (PORTBbits.RB15 == 1) {
        return kp_getSymbol(0, 2);
    }
    LATBbits.LATB9 = 0;
    
    
    LATBbits.LATB10 = 1;
    if (PORTBbits.RB12 == 1) {                                         
        return kp_getSymbol(3, 1);
    } else if (PORTBbits.RB13 == 1) {
        return kp_getSymbol(2, 1);
    } else if (PORTBbits.RB14 == 1) {
        return kp_getSymbol(1, 1);
    } else if (PORTBbits.RB15 == 1) {
        return kp_getSymbol(0, 1);
    }
    LATBbits.LATB10 = 0;
    
    LATBbits.LATB11 = 1;  
    if (PORTBbits.RB12 == 1) {                                         
        return kp_getSymbol(3, 0);
    } else if (PORTBbits.RB13 == 1) {
        return kp_getSymbol(2, 0);
    } else if (PORTBbits.RB14 == 1) {
        return kp_getSymbol(1, 0);
    } else if (PORTBbits.RB15 == 1) {
        return kp_getSymbol(0, 0);
    }
    LATBbits.LATB11 = 0;
    
    

	return 'N'; //if nothing is found
}