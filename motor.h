#ifndef MOTOR_H   /* Guard against multiple inclusion */
#define MOTOR_H

#define PS LATEbits.LATE0
#define PHASE1 LATEbits.LATE1
#define PHASE2 LATEbits.LATE2
#define PHASE3 LATEbits.LATE3
#define PHASE4 LATEbits.LATE4

void motor_setFeederDirection(int direction);
void motor_setCutterDirection(int direction);

void motor_stepCutterDown();
void motor_stepCutterUp();
void motor_stepFeeder(int steps);
void motor_feed(int distance);
void motor_cut();

#endif