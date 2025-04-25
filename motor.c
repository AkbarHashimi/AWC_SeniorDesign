#include "xc.h"
#include "motor.h"
#include "misc.h"

//stepper motor functions

const float cutting_distance = 100; //distance knife will travel
const float wheel_radius = .3;//in cm
const float step_angle = 1.8; //in degrees
								//from "SM_42BYG011-25"
const float dps = step_angle * wheel_radius; //distance per step
//etc...

//we want one step and one step only (one signal is changed, not both)

//1-16
//17-32
//33-48
//49-64

int motor_states[4][2] = {
    {0, 1},
    {0, 0},
    {1, 0},
    {1, 1}
};

static int feeder_index = 0;
static int feeder_direction = 1; // -1 for backward, 1 for forward

static int cutter_index = 0;
static int cutter_direction = 1; // -1 for backward, 1 for forward

void motor_setCutterDirection(int direction) {
    switch (direction) {
        case 1:
        case -1: cutter_direction = direction;
        default: cutter_direction = -1;
    }
}

void motor_setFeederDirection(int direction) {
    switch (direction) {
        case 1:
        case -1: feeder_direction = direction;
        default: feeder_direction = 1;
    }
}

void motor_stepCutter() {
	cutter_index += cutter_direction;
    if (cutter_index > 3) {
        cutter_index = 0;
    } else if (cutter_index < 0) {
        cutter_index = 3;
    }
    
    PHASE3 = motor_states[cutter_index][0];
    PHASE4 = motor_states[cutter_index][1];
}

void motor_stepFeeder(int steps) {
    // ~1600 us delay max
	for (int i = 0; i < steps; i++) {
        feeder_index += feeder_direction;
        if (feeder_index > 3) {
            feeder_index = 0;
        } else if (feeder_index < 0) {
            feeder_index = 3;
        }
        PHASE1 = motor_states[feeder_index][0];
        PHASE2 = motor_states[feeder_index][1];
        
        delay_us(5000);
	}
}

void motor_feed(int distance) { //distance in centimeters, can only be int input
	float dps = step_angle * wheel_radius;
	int steps = distance / dps; //dps = distance/step;
	motor_stepFeeder(steps);
}

void motor_cut() {
	int numSteps = cutting_distance / dps;
	for (int i = 0; i < numSteps; i++) {
		motor_stepCutter();
		delay_us(1900); //shorter delay for faster cutting speed
	}
	
    cutter_direction = -(cutter_direction);
    delay_ms(250);
    
	for (int i = 0; i < numSteps; i++) {
		motor_stepCutter();
		delay_us(2200); //slightly relaxed journey back to resting position
	}
    
    cutter_direction = -(cutter_direction);
}