#ifndef LCD_H   /* Guard against multiple inclusion */
#define LCD_H

#include <xc.h>

/*
#define RS LATDbits.LATD1
#define RW LATDbits.LATD2
#define E LATDbits.LATD3
#define DB4 LATDbits.LATD4
#define DB5 LATDbits.LATD5
#define DB6 LATDbits.LATD6
#define DB7 LATDbits.LATD7
 */

#define RS LATDbits.LATD1
#define RW LATDbits.LATD2
#define E LATDbits.LATD3
#define DB0 LATDbits.LATD4
#define DB1 LATDbits.LATD5
#define DB2 LATDbits.LATD6
#define DB3 LATDbits.LATD7
#define DB4 LATFbits.LATF0
#define DB5 LATFbits.LATF1
#define DB6 LATEbits.LATE0
#define DB7 LATEbits.LATE1

void lcd_setSignals(int rs, int rw, int d7a, int d6a, int d5a, 
				int d4a, int d7b, int d6b, int d5b, int d4b);
void lcd_print(char message[], int size, int row, int column);
void lcd_printChar(char character);
void lcd_init();
void lcd_shiftCursor(int RL);
void lcd_scroll(int RL);
int lcd_busy();
void lcd_clear();
void lcd_setDD(int address);
void lcd_printRegister(int register);

#endif