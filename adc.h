#ifndef ADC_H
#define ADC_H

/*
 
 * Considerations:
 * ADC interrupts must read from the buffer THEN clear the interrupt flag AFTER the buffer is read.
 * Max sample speed is 400 ksps
 * Sample time minimum is 200 ns
 
 
 */


//Pre: ADC must be OFF
//Post: Analog Pins that are used will be put into analog mode
void configANPins();

//Pre: ADC must be OFF
//Post: Configures the two MUX inputs A and B
void configIntoMux();

//Pre: ADC must be OFF
//Post: Configures the format of the result buffer - currently a 32 bit unsigned int format
//with rightmost 10 bits being data, the rest is 0
void setOutputFormat();

//Pre: ADC must be OFF
//Post: Sets Conversion to happen automatically
void setSampleConvTrigger();

//Pre: ADC must be OFF
//Post: Sets Voltage Reference for HIGH and LOW for system
void setVoltageRefs();

//Pre: ADC must be OFF
//Post: Sets input scan mode to OFF
void selectScanMode();

//Pre: ADC must be OFF
//Post: Sets the rate of samples the interrupt should occur
//in our case 2 Samples are converted then the interrupt happens
void setConvPerInterrupt();

//Pre: ADC must be OFF
//Post: Buffer Size is set to either 8 bit or 16 bit mode - we are using 16 bit
void setBufferFillMode();


//Pre: ADC must be OFF
//Post: Configures the ADC Clock Source and Speed
/*
    
 * Clock source is PBCLK
 * TAD = 18*TPB 18 times the PBCLK - ADC Clock Speed
 * Auto Sample Time bits
 
 
 */
void configADC_Clock();

//Pre: ADC must be OFF
//Post: sets sample time of ADC
void setSampleTime();

//Pre: ADC must be OFF
//Post: sets the ADC to alternate between sampling TSENSE and CSENSE
void setAlternateMode();

//Pre: ADC must be OFF
//Post: 
void adc_init();

//Pre: adc_init() should be called first to initialize config registers
//Post: Turns on ADC
void adc_on();

//Pre: None
//Post: Turns ADC on
void adc_off();

//Pre: ADC should be ON
//Post: 
void stopSampling();

//Pre: ADC should be ON
//Post: 
void startSampling();

//Pre: Set auto sample mode
//Post:
void setAutoSample();

#endif