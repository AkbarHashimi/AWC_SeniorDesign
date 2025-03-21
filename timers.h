#ifndef TIMERS_H
#define TIMERS_H

//Return the current Core timer clock
//Core Timer increments at SYSCLOCK/2
int getCP0(void);

//Set's the core timer. Can be used to reset to zero
void setCP0(int a);

//Reset core time.
void resetCP0(void);

//Set the Compare register. This is used to compare to the core timer.
//If they are equal, the CPU asserts an interrupt that can only be cleared
//once Compare is written to
void setCompare(int a);

//Get the Compare register value
int getCompare(void);

//Set and initialize Timer1
//Requires a 16 bit int to represent a match value
void setTimer1(int a);

/*  Set and initialize Timer2
 *      a is 16 bit match value.
 *  Timer 2 and 4 can be set as 32 bit wide timers
 *      a would be 32 bit match value
 */
void setTimer2(int a);


/*  Set and initialize Timer3
 *      if Timer2 is set to 32 bits, Timer 3 is disabled
 */
void setTimer3(int a);


/*  Set and initialize Timer4
 *      a is 16 bit match value.
 *  Timer 2 and 4 can be set as 32 bit wide timers
 *      a would be 32 bit match value
 */
void setTimer4(int a);


/*  Set and initialize Timer5
 *      if Timer4 is set to 32 bits, Timer 5 is disabled
 */
void setTimer5(int a);
#endif