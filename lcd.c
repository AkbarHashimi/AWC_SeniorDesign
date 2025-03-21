//Custom LCD functions for CMPE492 - Spring 2025
//Derived from HD44780U datasheet

#include <xc.h>
#include "lcd.h"
#include "misc.h"

void lcd_setSignals(int rs, int rw, int d7a, int d6a, int d5a, 
				int d4a, int d7b, int d6b, int d5b, int d4b) {
   
    //LCD has 10 pins: {RS, R/W, DB7, DB6, DB5, DB4, DB3, DB2, DB1, DB0}, and an enable bit
    //Performing functions on the LCD requires a specific setup from the signals above
    //Flicking the enable bit will send this instruction into the HD44780U
    
	//Implemented for 4-bit communication
	//This means that DB3:DB0 are not used when sending instructions to LCD
	//So we cannot write the whole byte DB7:DB0 in one go
	//Instead, DB7:DB4 will send the upper four bits, and then the bottom four bits.
	//This means the enable bit needs to be flipped twice for each section of the byte
	//RS and RW remain constant through both iterations
  
	RS = rs;
	RW = rw;
	DB7 = d7a;
	DB6 = d6a;
	DB5 = d5a; 
	DB4 = d4a;
	DB3 = d7b;
	DB2 = d6b;
	DB1 = d5b; 
	DB0 = d4b;
	E = 1;
	delay(100000); //pause for instruction to run
	E = 0;
	return;
}

/*
//Our primary interest is to print strings and characters onto the LCD:

void lcd_print(char message[], int size, int row, int column);
void lcd_printChar(char character);

//But preliminary and auxiliary functions are necessary:

void lcd_init();
void lcd_shiftCursor(int RL);
void lcd_scroll(int RL);
int lcd_busy();
void lcd_clear();
void lcd_setDD(int address);

*/

void lcd_init() {
	//function set: {0, 0, 0, 0, 1, DL, N, F, *, *}; * = don't care
	//DL = 0: 4 bit communication
	//N = 1: 2 lines on LCD
	//F = 0: 5 x 8 dot characters
	lcd_setSignals(0, 0, 0, 0, 1, 1, 1, 0, 0, 0);
	
	//entry mode set: {0, 0, 0, 0, 0, 0, 0, 1, I/D, S}
	//I/D = 1; AC increments after each write command
	//S = 0; display does not shift
	lcd_setSignals(0, 0, 0, 0, 0, 0, 0, 1, 1, 0);
    
    //display on/off control: {0, 0, 0, 0, 0, 0, 1, D, C, B}
    //D = 1: display is on
    //C = 1: cursor is displayed
    //B = 1: character blinks with cursor
    lcd_setSignals(0, 0, 0, 0, 0, 0, 1, 1, 1, 1);
	return;
}

void lcd_shiftCursor(int RL) {
	// R/L = 1: shift right; R/L = 0: shift left
	// {0, 0, 0, 0, 0, 1, S/C, R/L, *, *}; * = don't care
	// S/C = 1: display shift; S/C = 0: cursor shift
	lcd_setSignals(0, 0, 0, 0, 0, 1, 0, RL, 0, 0);
	return;
}

int lcd_busy() {
	lcd_setSignals(0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
	TRISBbits.TRISB7 = 1;    //set RB7 to input before reading busy flag
    int val = PORTBbits.RB7; //read busy flag
    TRISBbits.TRISB7 = 0;    //B7 back to output
	return val;
}

void lcd_clear() {
	lcd_setSignals(0, 0, 0, 0, 0, 0, 0, 0, 0, 1); //clear screen command
	return;
}

void lcd_setDD(int address) {
    int d4b = (address >> 0) & 0x01;
    int d5b = (address >> 1) & 0x01;
    int d6b = (address >> 2) & 0x01;
    int d7b = (address >> 3) & 0x01;
    int d4a = (address >> 4) & 0x01;
    int d5a = (address >> 5) & 0x01;
	int d6a = (address >> 6) & 0x01; 
	
	lcd_setSignals(0, 0, 1, d6a, d5a, d4a, d7b, d6b, d5b, d4b);

	return;
}

void lcd_printChar(char character) { 
    //characters can be represented in binary <'1' == 00110001b>, and are explicitly in C
    //We need to print the character onto LCD by putting it's binary representation into the DDRAM
    //So the setup for the LCD to write into DDRAM {1, 0, b0, b1, b2, b3, b4, b5, b6, b7, b8}
    //Setting the DDRAM address tells the LCD to start writing into DDRAM, and not CGRAM
    //Boundaries for LCD row: top[0x00:0x27], bottom[0x40, 0x67]
    //By default, the first index prints the character immediately to the first cell of the LCD

    //So:
    //Break character into binary digits
    //Set up outputs for writeToDDRAM() <1, 0, b0, b1, b2, b3, b4, b5, b6, b7, b8>
    //Set enable bit

    
	int d7a = (character >> 7) & 0b1; //high- order bits first
	int d6a = (character >> 6) & 0b1;
	int d5a = (character >> 5) & 0b1;
	int d4a = (character >> 4) & 0b1;
	int d7b = (character >> 3) & 0b1; //write low-order bits
	int d6b = (character >> 2) & 0b1;
	int d5b = (character >> 1) & 0b1;
	int d4b = (character >> 0) & 0b1; 
	lcd_setSignals(1, 0, d7a, d6a, d5a, d4a, d7b, d6b, d5b, d4b);

	return;
}

void lcd_print(char string[], int size, int row, int column) {
	//We can assume that the user knows that writing over the lines can be scrolled over to
	//Write to AC: {0, 0, 1, ADD, ADD, ADD, ADD, ADD, ADD, ADD}
	
    
	int address = (row * 0x40) + column; //first term will be 0 if row is 1, so we start at 0x00 before adding columns
	address = address - 1; //AC increments after writing this instruction
	
	lcd_setDD(address);
    
	
	for (int i = 0; i < size; i++) {
		lcd_printChar(string[i]);
	}
	
	return;
}

void lcd_printRegister(int address) {
    lcd_clear();
    int temp;
    for (int i = 0; i < 8; i++) {
        temp = (address >> ((7 - i) << 2)) & 0xF;
        if (temp > 10) {
            lcd_printChar(0x37 + temp);
        } else {
            lcd_printChar(0x30 + temp);
        }
    }
    return;
}