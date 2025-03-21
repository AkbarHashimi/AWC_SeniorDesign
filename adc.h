#ifndef ADC_H
#define ADC_H

/*
 
 * Considerations:
 * ADC interrupts must read from the buffer THEN clear AFTER the buffer is read.

 
 
 */



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
void setAlternateMode();

void setupADC();

void turnOnADC();
void turnOffADC();





#endif