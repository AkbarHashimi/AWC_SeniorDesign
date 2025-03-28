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

//Pre: ADC must be OFF
//Post: 
void adc_init()
{
    configANPins();
    configIntoMux();
    setAlternateMode();
    setOutputFormat();
    setSampleConvTrigger();
    setVoltageRefs();
    selectScanMode();
    setConvPerInterrupt();
    setBufferFillMode();
    configADC_Clock();
    setSampleTime();
}

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

void setSampleConvTrigger()
{
    //Setting the conversion trigger source selection bits
    
    AD1CON1SET = 0x000000E0;
}

void setVoltageRefs()
{
    //Set voltage reference source
    //VREFH = AVDD
    //VREFL = AVSS
    
    AD1CON2CLR = 0x0000A000;
    
}

void selectScanMode()
{
    //Disable scan mode
    
    AD1CON2CLR = 0x00000400;
}

void setConvPerInterrupt()
{
    //Here we take 2 conversions before we generate an Interrupt
    
    //We want SMPI <3:0> 0001
    
    AD1CON2CLR = 0x00000038;
    AD1CON2SET = 0x00000004;
}

void setBufferFillMode()
{
    //There are two modes:
    //1. Use buffers of size 16
    //2. use buffers of size 8
    
    //Depending 
    //For now we are choosing size 16
    
    AD1CON2CLR = 0x00000002;
}

void configADC_Clock()
{
    //Select the ADC Conversion Clock and Prescaler
    //We are using PBCLK and scaling it down from 72 MHz to 4 MHz
    
    //set bits for ADC conversion clock prescaler
    
    AD1CON3SET = 0x0000008; //divide by 9
    
    //clear bits for both prescaler and ADC Conversion Clock Source bit
    
    AD1CON3CLR = 0x000080F7;
}

//Pre: ADC must be OFF
//Post: sets sample time of ADC
void setSampleTime()
{
    //SAMC set to 00001 - 1 Tad
    
    AD1CON3SET = 0x00000100;
    AD1CON3CLR = 0x00001E00;
    
}

//Pre: ADC should be ON
//Post: 
void startSampling()
{
    AD1CON1bits.ASAM = 1;
}

//Pre: ADC should be ON
//Post: 
void stopSampling()
{
    AD1CON1bits.ASAM = 0;
}


//Pre: adc_init() should be called first to initialize config registers
//Post: Turns on ADC
void adc_on()
{
    AD1CON1bits.ON = 1;
}


//Pre: None
//Post: Turns ADC on
void adc_off()
{
    AD1CON1bits.ON = 0;
}