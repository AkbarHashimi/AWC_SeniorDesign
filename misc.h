#ifndef MISC_H   /* Guard against multiple inclusion */
#define MISC_H

#define DEBUG LATEbits.LATE5

void delay(int num);
void delay_us(int us);
void delay_ms(int ms);
void misc_blinkDebug(int numTimes);
int misc_modifyTotal(int total, char input);
int getBatchSize(char message[], int size);
void testKeypad();
void testLCD();

#endif