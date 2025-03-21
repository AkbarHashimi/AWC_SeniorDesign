#include "xc.h"
#include "keypad.h"
#include "lcd.h"
#include "misc.h"

void delay(int num){ //mostly obsolete version of the delay funcitons below
    for (int i = 0; i < num; i++){
        _nop();      
    }
}

void delay_us(int us) { //accurate to +- 1 us
    for (int i = 0; i < (2 * us) - 1; i++) {
        _nop();
    }
}

void delay_ms(int ms) { //accurate to +- 1 ms
    for (int i = 0; i < (2000 * ms); i++) {
        _nop();
    }
}

void misc_blinkDebug(int numTimes) {
    for (int i = 0; i < numTimes; i++) { //blink debug n times
        DEBUG = 1;
        delay(1000000);
        DEBUG = 0;
        delay(1000000);
    }
    return;
}

int misc_modifyTotal(int total, char input) {

    //takes parameter total and updates it depending on the inputted character
    //inputted character is scanned by keypad
    
    //because it reads as a character, there needs to be a function to track
    //the total length/amount after each button press
    
	switch (input) {
		case '0':										//if input is a numeric digit
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': return (total * 10) + (input - 48); 	//shift current digits to left, 
														//convert input from ascii to digit,
														//then append digit to total with addition

		case 'D': return (total / 10);					//if digit is deleted, move all digits right,
														//truncating off removed digit

		default: return total;							//do nothing in case of 'N' or 'E'
	}
}
int misc_getBatchSize(char message[], int size) { 

	//returns the value asked for in message[]
    
    //Scans for keypad input until user presses a button
    //If the user selected a digit, print that digit on the screen,
    //  and keep an accumulating, numerical total
    //If the user chose to delete, replace the last character with a space
    //If the user chooses to exit, the loop ends, and the total is returned

	lcd_clear(); 						
	lcd_print(message, size, 0, 0); //prompt the user			
	lcd_setDD(0x40);                //place cursor on second row

	int position = 0;	//for cursor position in LCD row
	char input = 'N';	//stores user input
	int total = 0;		//stores total value

	do {
		input = kp_scanForInput(); 				//check for button input
												
		if (input == 'N') { 					//if no valid buttons pressed
			continue;							//do nothing and rescan	
		}

		total = misc_modifyTotal(total, input);		//returns total after appending/deleting new input
		
		if (input == 'D' && position > 1) { 	//if we are deleting,
			position = position - 1; 			//go to previous character
            lcd_setDD(0x40 + position);         //place cursor over character to delete
            lcd_printChar(' ');                 //print empty character (delete character)
            lcd_setDD(0x40 + position);         //move cursor back over empty space
			
		} else if (input != 'E') {              //if not deleting or entering,
            lcd_printChar(input);               //print numerical character
        }

		delay_ms(500); //delay so one button pressed isn't accidentally read twice

	} while (input != 'E');
	return total; //return entered amount to main
}
void testKeypad() {
    char input = 'N';
    do {
        input = kp_scanForInput();
        if (input != 'N' && input != 'E') {
            misc_blinkDebug(1);
        }
    } while (input != 'E');
    DEBUG = 1;
}
void testLCD() {
    lcd_init();
    lcd_printChar('H');
    lcd_printChar('i');
    delay(1000000);
    lcd_clear();
    
    lcd_print("Testing?", 8, 0, 0);
    delay_ms(1000*10);
    
    lcd_setDD(0x00 + 7);
    lcd_printChar('!');
}