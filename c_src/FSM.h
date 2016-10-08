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

#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include "motor_control.h"

#define IN_LINE 1
#define OUT_LINE 0

#ifndef FSM_H
#define FSM_H

extern uint8 button_flag;
    
    
extern uint8 s_fl;
extern uint8 s_fr;
extern uint8 s_l;
extern uint8 s_r;
extern uint8 s_m;
extern uint8 s_b;



struct State;
typedef void state_logic(struct State*);

struct State{
    state_logic* next_state;
};

state_logic unknown, straight, front_out, turn_left, turn_right;


void init_fsm(void);
void start_sensor_isr();
void FSM();

//void start(struct State* state);
void unknown(struct State* state);
void straight(struct State* state);
void front_out(struct State* state);
void intersection(struct State* state);

void turn_left(struct State* state);
void turn_right(struct State* state);

void adjust_right(struct State* state);
void adjust_left(struct State* state);






#endif
/*  state template

void foobar(struct State* state);

*/


/* [] END OF FILE */
