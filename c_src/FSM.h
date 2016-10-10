/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/


#ifndef FSM_H
#define FSM_H

#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include "motion_actuator.h"
#include "motor_control.h"
#include "RF_handler.h"
#include "defines.h"



//#define ANGLE_THRESHOLD 20





uint8 pid_start;

uint8 rf_start;

struct State;
typedef void state_logic(struct State*,motion_type current_motion,decision_type decision_input);

struct State{
    state_logic* next_state;
   	decision_type current_decision;
};

//state_logic unknown, straight, front_out, turn_left, turn_right;


void init_FSM();
void FSM();

//void start(struct State* state);
void unknown(struct State* state,uint8 flag,decision_type decision_input);
void straight(struct State* state,uint8 flag,decision_type decision_input);

void turn_left(struct State* state,uint8 flag,decision_type decision_input);
void turn_right(struct State* state,uint8 flag,decision_type decision_input);

void turn_around(struct State* state,uint8 flag,decision_type decision_input);

uint8 get_pid_start();
void set_pid_start(uint8 start);




#endif
/*  state template

void foobar(struct State* state);

*/


/* [] END OF FILE */
