#include "adc.h"
#include "misc.h"

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
    AD1PCFGCLR = 0x0000000C;  //make AN2 and AN3 analog input and AN12
    AD1PCFGSET = 0x0000FFF3; //all pins besides AN2 and AN3 are set to digital

    
    //Port B is where AN2 and AN3 are located
    //Set their TRIS bits to 1 to read as input
    
    TRISBbits.TRISB2 = 0b1;
    TRISBbits.TRISB3 = 0b1;
    
    
    
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
    
    AD1CHSbits.CH0NA = 0b0;
    AD1CHSbits.CH0NB = 0b0;
    AD1CHSbits.CH0SA = 0x2;    
    AD1CHSbits.CH0SB = 0x3; 
    
    
    
    
}



void setOutputFormat()
{
    //Here we set the output format of the buffer
    //We use a sign extended 32 bit integer unsigned
    //only the 10 Least Significant (Rightmost) Bits are data
    
    
    AD1CON1bits.FORM = 0x4;
    
}

void setSampleConvTrigger()
{
    //Setting the conversion trigger source selection bits
    AD1CON1bits.SSRC = 0x0;
    AD1CON1bits.CLRASAM = 0x0;
    AD1CON1bits.ASAM = 0x0;
    AD1CON1bits.SAMP = 0x0;   
    
}

void setVoltageRefs()
{
    //Set voltage reference source
    //VREFH = AVDD
    //VREFL = AVSS
    
    AD1CON2bits.VCFG = 0x0;
    
}

void selectScanMode()
{
    //Disable scan mode
    
    AD1CON2bits.CSCNA = 0x0;
}

void setConvPerInterrupt()
{
    //Here we take 2 conversions before we generate an Interrupt
    
    //We want SMPI <3:0> 0001
    
    AD1CON2bits.SMPI = 0x1;
}

void setBufferFillMode()
{
    //There are two modes:
    //1. Use buffers of size 16
    //2. use buffers of size 8
    
    //Depending 
    //For now we are choosing size 16
    
    AD1CON2bits.BUFM = 0b0;
}

void configADC_Clock()
{
    //Select the ADC Conversion Clock and Prescaler
    //We are using PBCLK and scaling it down from 72 MHz to 4 MHz
    
    //set bits for ADC conversion clock prescaler
    
    AD1CON3bits.ADCS = 0x8; //divide by 9
    
    //clear bits for both prescaler and ADC Conversion Clock Source bit
    
    AD1CON3bits.ADRC = 0b0;
    
}

//Pre: ADC must be OFF
//Post: sets sample time of ADC
void setSampleTime()
{
    //SAMC set to 00001 - 1 Tad
    
    AD1CON3bits.SAMC = 0b1;
    
}

//Pre: ADC should be ON
//Post: 
void startSampling()
{
    AD1CON1bits.SAMP = 1;
}

//Pre: ADC should be ON
//Post: 
void stopSampling()
{
    AD1CON1bits.SAMP = 0;
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

//Pre: Set auto sample mode
//Post:
void setAutoSample()
{
    AD1CON1bits.ASAM = 1;
}


int grabOneSample()
{
    startSampling();
    delay_ms(100);
    stopSampling();
    
    while (!(AD1CON1 & 0x0001));
    int sampleVal = ADC1BUF0;
    return sampleVal;
    
}

