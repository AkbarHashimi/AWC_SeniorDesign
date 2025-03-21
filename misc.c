#include "xc.h"
#include "keypad.h"
#include "lcd.h"
#include "misc.h"

void delay(int num){
    for (int i = 0; i < num; i++){
        _nop();      
    }
}

void delay_us(int us) {
    for (int i = 0; i < (2 * us) - 1; i++) {
        _nop();
    }
}

void delay_ms(int ms) {
    for (int i = 0; i < (2000 * ms); i++) {
        _nop();
    }
}

void misc_blinkDebug(int numTimes) {
    
    for (int i = 0; i < numTimes; i++) {
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

	//will be inside main 
	//it's purpose is to return the value we are asking for in "message"
    
    //scans for keypad input until 'E' or "enter" is pressed
    //if button pressed is not enter, tracks the character user touched
    //outputs this character on the LCD screen for user convenience
    //numerical total is kept track via 
    //characters can be deleted, and changes are t
    //tracks the total by converting

	lcd_clear(); 						//clear after booting
	lcd_print(message, size, 1, 1);			//prompt user to input
	lcd_setDD(0x40);					//place cursor on second row

	int position = 1;	//for cursor position in LCD row
	char input = 'N';	//stores user input
	int total = 0;		//stores total value
	

	do {
		input = kp_scanForInput(); 				//check for button input
												//returns null if no buttons pressed
												
		if (input == 'N') { 					//if no valid buttons pressed
			continue;							//do nothing and rescan		
		}

		total = misc_modifyTotal(total, input);		//returns total after appending/deleting new input
		
		
		if (input == 'D' && position > 1) { 	//if we are deleting,
			position = position - 1; 			//go to previous character
            lcd_setDD(0x40 + position);         //place cursor over character to delete
            lcd_printChar(' ');                 //print empty character (delete character)
            lcd_setDD(0x40 + position);         //move cursor back over empty space
			
		} else if (input != 'E') {              //if not deleted and not entering,
            lcd_printChar(input);               //print numerical character
        }

		//delay_ms(500); //make our own delay function

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
    delay(1000000);
    
    lcd_setDD(0x00 + 7);
    lcd_printChar('!');
}