#include <xc.h>

//Return the current Core timer clock
//Core Timer increments at SYSCLOCK/2
int getCP0(void){
    return _CP0_GET_COUNT();
}

//Set's the core timer. Can be used to reset to zero
void setCP0(int a){
    _CP0_SET_COUNT(a);
}

//Reset core time.
void resetCP0(void){
    _CP0_SET_COUNT(0);
}

//Set the Compare register. This is used to compare to the core timer.
//If they are equal, the CPU asserts an interrupt that can only be cleared
//once Compare is written to
void setCompare(int a){
    _CP0_SET_COMPARE(a);
}

//Get the Compare register value
int getCompare(void){
    _CP0_GET_COMPARE();
}

//Set and initialize Timer1
//Requires a 16 bit int to represent a match value
void setTimer1(int a){
    // 1 = Timer is Enabled, 0 = Timer is Disabled
    T1CON.TON = 0b1;  
    
    // Stop In Idle Mode Bit. 
    //1 = Discontinue operation when in Idle Mode; 0 = Continue when in Idle Mode
    T1CON.SIDL = 0b1;  
    
    // Asynchronous Timer Write Disable Bit. 
    // 1 = Writes to TMR1 are ignored until pending write operation completes
    // 0 = Back-to-back writes are enabled (Legacy Asynchronous Timer functionality)
    T1CON.TWDIS = 0b1;  
    
    /*
     * Asynchronous Timer Write in Progress bit
     * In Asynchronous Timer mode: (TWDIS = 0b0)
     *         1 = Asynchronous write to TMR1 register in progress
     *         0 = Asynchronous write to TMR1 register complete
     * 
     * In Synchronous Timer mode:
     *          This bit is read as ?0?.
     */
    //T1CON.TWIP; // read only bit
    
    /*  Timer Gated Time Accumulation Enable bit
     *      When TCS = 1:
     *      This bit is ignored.
     *      When TCS = 0:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
    T1CON.TGATE = 0b0;
    
    /*  Timer Input Clock Prescale Select bits
     *      11 = 1:256 prescale value
     *      10 = 1:64 prescale value
     *      01 = 1:8 prescale value
     *      00 = 1:1 prescale value    
     */
    T1CON.TCKPS = 0b00;
    
    
    /*  Timer External Clock Input Synchronization Selection bit
     *      When TCS = 1:
     *          1 = External clock input is synchronized
     *          0 = External clock input is not synchronized
     *      When TCS = 0:
     *          This bit is ignored.   
     */
    T1CON.TSYNC = 0b1;
    
    
    /*  Timer Clock Source Select bit
     *      1 = External clock from TxCKI pin
     *      0 = Internal peripheral clock     * 
     */
    T1CON.TCS = 0b0;
    
    
    /*  Timer Register
     *      16bit timer Count. Resets to 0
     */
    TMR1 = 0x0000;
    
     /*  Period Register
     *      This register provides the TMRx match value.
     */
    PR1 = a;    
}

/*  Set and initialize Timer2
 *      a is 16 bit match value.
 *  Timer 2 and 4 can be set as 32 bit wide timers
 *      a would be 32 bit match value
 */
void setTimer2(int a){
    // 1 = Timer is Enabled, 0 = Timer is Disabled
    T2CON.TON = 0b1;  
    
    // Stop In Idle Mode Bit. 
    //1 = Discontinue operation when in Idle Mode; 0 = Continue when in Idle Mode
    T2CON.SIDL = 0b1;  
 
    
    /*  Timer Gated Time Accumulation Enable bit
     *      When TCS = 1:
     *      This bit is ignored.
     *      When TCS = 0:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
    T2CON.TGATE = 0b0;
    
    /*  Timer Input Clock Prescale Select bits
     *      111 = 1:256 prescale value
     *      110 = 1:64 prescale value
     *      101 = 1:32 prescale value 
     *      100 = 1:16 prescale value
     *      011 = 1:8 prescale value
     *      010 = 1:4 prescale value
     *      001 = 1:2 prescale value
     *      000 = 1:1 prescale value    
     */
    T2CON.TCKPS = 0b000;
    
    
    /*  32-bit Timer Mode Select bit
     *      1 = TMRx and TMRy form a 32-bit timer
     *      0 = TMRx and TMRy form separate 16-bit timer   
     */
    T2CON.T32 = 0b0;
    
    
    /*  Timer Clock Source Select bit
     *      1 = External clock from TxCKI pin
     *      0 = Internal peripheral clock     * 
     */
    T2CON.TCS = 0b0;
    
    
    /*  Timer Register
     *      16bit timer Count. Resets to 0
     */
    TMR2 = 0x0000;
    
     /*  Period Register
     *      This register provides the TMRx match value.
     */
    PR2 = a; 
}


/*  Set and initialize Timer3
 *      if Timer2 is set to 32 bits, Timer 3 is disabled
 */
void setTimer3(int a){
    // 1 = Timer is Enabled, 0 = Timer is Disabled
    T3CON.TON = 0b1;  
    
    // Stop In Idle Mode Bit. 
    //1 = Discontinue operation when in Idle Mode; 0 = Continue when in Idle Mode
    T3CON.SIDL = 0b1;  
 
    
    /*  Timer Gated Time Accumulation Enable bit
     *      When TCS = 1:
     *      This bit is ignored.
     *      When TCS = 0:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
    T3CON.TGATE = 0b0;
    
    /*  Timer Input Clock Prescale Select bits
     *      111 = 1:256 prescale value
     *      110 = 1:64 prescale value
     *      101 = 1:32 prescale value 
     *      100 = 1:16 prescale value
     *      011 = 1:8 prescale value
     *      010 = 1:4 prescale value
     *      001 = 1:2 prescale value
     *      000 = 1:1 prescale value    
     */
    T3CON.TCKPS = 0b000;
    
    
    /*  Timer Clock Source Select bit
     *      1 = External clock from TxCKI pin
     *      0 = Internal peripheral clock     * 
     */
    T3CON.TCS = 0b0;
    
    
    /*  Timer Register
     *      16bit timer Count. Resets to 0
     */
    TMR3 = 0x0000;
    
     /*  Period Register
     *      This register provides the TMRx match value.
     */
    PR3 = a;     
}


/*  Set and initialize Timer4
 *      a is 16 bit match value.
 *  Timer 2 and 4 can be set as 32 bit wide timers
 *      a would be 32 bit match value
 */
void setTimer4(int a){
    // 1 = Timer is Enabled, 0 = Timer is Disabled
    T4CON.TON = 0b1;  
    
    // Stop In Idle Mode Bit. 
    //1 = Discontinue operation when in Idle Mode; 0 = Continue when in Idle Mode
    T4CON.SIDL = 0b1;  
 
    
    /*  Timer Gated Time Accumulation Enable bit
     *      When TCS = 1:
     *      This bit is ignored.
     *      When TCS = 0:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
    T4CON.TGATE = 0b0;
    
    /*  Timer Input Clock Prescale Select bits
     *      111 = 1:256 prescale value
     *      110 = 1:64 prescale value
     *      101 = 1:32 prescale value 
     *      100 = 1:16 prescale value
     *      011 = 1:8 prescale value
     *      010 = 1:4 prescale value
     *      001 = 1:2 prescale value
     *      000 = 1:1 prescale value    
     */
    T4CON.TCKPS = 0b000;
    
    
    /*  32-bit Timer Mode Select bit
     *      1 = TMRx and TMRy form a 32-bit timer
     *      0 = TMRx and TMRy form separate 16-bit timer   
     */
    T4CON.T32 = 0b0;
    
    
    /*  Timer Clock Source Select bit
     *      1 = External clock from TxCKI pin
     *      0 = Internal peripheral clock     * 
     */
    T4CON.TCS = 0b0;
    
    
    /*  Timer Register
     *      16bit timer Count. Resets to 0
     */
    TMR4 = 0x0000;
    
     /*  Period Register
     *      This register provides the TMRx match value.
     */
    PR4 = a;     
}


/*  Set and initialize Timer5
 *      if Timer4 is set to 32 bits, Timer 5 is disabled
 */
void setTimer5(int a){
    // 1 = Timer is Enabled, 0 = Timer is Disabled
    T5CON.TON = 0b1;  
    
    // Stop In Idle Mode Bit. 
    //1 = Discontinue operation when in Idle Mode; 0 = Continue when in Idle Mode
    T5CON.SIDL = 0b1;  
 
    
    /*  Timer Gated Time Accumulation Enable bit
     *      When TCS = 1:
     *      This bit is ignored.
     *      When TCS = 0:
     *      1 = Gated time accumulation is enabled
     *      0 = Gated time accumulation is disabled
     */
    T5CON.TGATE = 0b0;
    
    /*  Timer Input Clock Prescale Select bits
     *      111 = 1:256 prescale value
     *      110 = 1:64 prescale value
     *      101 = 1:32 prescale value 
     *      100 = 1:16 prescale value
     *      011 = 1:8 prescale value
     *      010 = 1:4 prescale value
     *      001 = 1:2 prescale value
     *      000 = 1:1 prescale value    
     */
    T5CON.TCKPS = 0b000;
    
    
    /*  32-bit Timer Mode Select bit
     *      1 = TMRx and TMRy form a 32-bit timer
     *      0 = TMRx and TMRy form separate 16-bit timer   
     */
    T5CON.T32 = 0b0;
    
    
    /*  Timer Clock Source Select bit
     *      1 = External clock from TxCKI pin
     *      0 = Internal peripheral clock     * 
     */
    T5CON.TCS = 0b0;
    
    
    /*  Timer Register
     *      16bit timer Count. Resets to 0
     */
    TMR5 = 0x0000;
    
     /*  Period Register
     *      This register provides the TMRx match value.
     */
    PR5 = a;     
}

