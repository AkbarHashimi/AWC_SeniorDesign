#include "adc.h"

#include <xc.h>
/*
 
void configANPins();
void configIntoMux();
void setOutputFormat();
void setSampleClockSource();
void setVoltageRefs();
void selectScanMode();
void setConvPerInterrupt();
void setBufferFillMode();
void setMuxToADCConnection();
void setADCClockSource();
void setSampleTime();
void setADCClockPrescaler();

void setupADC();

void turnOnADC();
void turnOffADC();
 
 
 */

//Note: use IFS1 to check if we are done
//IFSx: Interrupt Flag Status register

void configANPins()
{
    //set the digital pins first
    //setting AD1PCFG<n> = 1 will make it a digital input
    
    //CLR,SET, and INV registers only modify values with '1', values with '0' are unmodified
    
    AD1PCFGSET = 0x0000FFF3; //all pins besides AN2 and AN3 are set to digital
    AD1PCFGCLR = 0x0000000C; //make AN2 and AN3 analog input
    
    //Port B is where AN2 and AN3 are located
    //Set their TRIS bits to 1 to read as input
    
    TRISBSET = 0x0000000C;
    
    
    
}


void configIntoMux()
{
    /* 
    
    Essentially the ADC uses an OP-AMP to read inputs
    Positive Terminal is for our reading in value
    Negative Terminal is our reference for LOW or 0
    
    In our design we are reading from 2 sensors, tension and compression sensor
    
    TSENSE or Tension sensor is on AN3
    CSENSE or Compression sensor is on AN2
    
    BOTH Negative Inputs for MUX A and B are VREFL - Voltage Reference LOW
    Positive Reference for MUX A - AN2 / CSENSE
    Positive Reference for MUX B - AN3 / TSENSE
    
    In Order to read from both inputs we must go into Alternating Mode which swaps between MUX A and B
    The order is initially at A, then swaps to B, then back to A, and repeat
     
    */
    
    //First - Clear Bits
    AD1CHSCLR = 0x8C8D0000;
            
    //Second - Set Bits
    AD1CHSSET = 0x03020000;
    
    
    
}

void setAlternateMode()
{
    /*    
     In Order to read from both inputs we must go into Alternating Mode which swaps between MUX A and B
     The order is initially at A, then swaps to B, then back to A, and repeat     
     */
    
    
    AD1CON2SET = 0x00000001;
    
    
}

void setOutputFormat()
{
    //Here we set the output format of the buffer
    //We use a sign extended 32 bit integer unsigned
    //only the 10 Least Significant (Rightmost) Bits are data
    
    
    AD1CON1SET = 0x00000400;
    
}

void setSampleClockSource()
{
    //Setting the conversion trigger source selection bits
    
    AD1CON1SET = 0x0000000E;
}

void setVoltageRefs()
{
    //Set voltage reference source
    //VREFH = AVDD
    //VREFL = AVSS
    
    AD1CON2CLR = 0x0000A000;
    AD1CON2SET = ;
}