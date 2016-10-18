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
/* [] END OF FILE */
#ifndef MOTION_ACUTATOR
#define MOTION_ACUTATOR
#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include "motor_control.h"
#include "defines.h"
#include "distance.h"

#define IN_LINE 1
#define OUT_LINE 0


volatile uint8 turned;
volatile uint16 timer_ovrflw; 
volatile uint8 turn_around_flag;
volatile uint8 side_sensor_turn_around_flag;

volatile uint8 button_flag;
    

    
volatile uint8 s_fl;
volatile uint8 s_fr;
volatile uint8 s_l;
volatile uint8 s_r;
volatile uint8 s_m;
volatile uint8 s_b;

struct motion_state;
typedef void motion_state_logic(struct motion_state*,decision_type decision, update_states fsm_state);
struct motion_state{
	motion_state_logic* next_state;
	motion_type current_motion;
	uint8 turned;
}motion_state;
void start_sensor_isr();

void init_motion_actuator();

uint8 recieve_next_state(decision_type decision);

uint8 get_state_complete();


//states 
void motion_straight(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_adjust_left(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_adjust_right(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_stop(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_turn_left(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_turn_right(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_turn_around(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_turning_buffer(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_stop_buffer(struct motion_state* m_state,decision_type decision, update_states fsm_state);
void motion_straight_buffer(struct motion_state* m_state,decision_type decision, update_states fsm_state);


void block_intersection_sensors();
void block_front_sensors();

#endif
