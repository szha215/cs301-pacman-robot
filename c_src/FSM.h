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
#include "pathfind.h"
#include "map.h"
#include "USB_UART.h"
//#define ANGLE_THRESHOLD 20





uint8 pid_start;

uint8 rf_start;


struct State;
typedef void state_logic(struct State*,motion_type current_motion,data_main *rf_data);

struct State{
    state_logic* next_state;
   	decision_type current_decision;
   	update_states fsm_state;
   	// int16_t *route;
      int16_t angle;
      int16_t current_node;
   	uint8_t level;
   	int16_t steps;
   	int16_t count;
   	int16_t step_counter;
      int16_t vertex_index;
      int16_t vertex_list_length;
   	uint8 food_index;
   	// data_main *rf_data;
};

//state_logic unknown, straight, front_out, turn_left, turn_right;


void init_FSM();
void FSM();

//void start(struct State* state);
void unknown(struct State* state,motion_type current_motion,data_main *rf_data);
void calculate(struct State* state,motion_type current_motion,data_main *rf_data);
void execute(struct State* state,motion_type current_motion,data_main *rf_data);
void update(struct State* state,motion_type current_motion,data_main *rf_data);
void recalculate(struct State* state,motion_type current_motion,data_main *rf_data);

uint8 get_pid_start();
void set_pid_start(uint8 start);

uint8 dip_read();


#endif
/*  state template

void foobar(struct State* state);

*/


/* [] END OF FILE */
