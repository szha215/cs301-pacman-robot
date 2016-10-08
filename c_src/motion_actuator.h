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

#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include "motor_control.h"

#define STRAIGHT 0
#define TURNING 1

#define TURN_LEFT 1
#define TURN_RIGHT 2
#define TURN_AROUND 4

#define IN_LINE 1
#define OUT_LINE 0

uint8 button_flag;
    
    
uint8 s_fl;
uint8 s_fr;
uint8 s_l;
uint8 s_r;
uint8 s_m;
uint8 s_b;

struct motion_state;
typedef void motion_state_logic(struct motion_state*,uint8 flag);
struct motion_state{
	motion_state_logic* next_state;
	uint8 current_flag;
}motion_state;
void start_sensor_isr();

void init_motion_actuator();

uint8 recieve_next_state(uint8 flag);

uint8 get_state_complete();


//states 
void motion_straight(struct motion_state* m_state,uint8 flag);
void motion_adjust_left(struct motion_state* m_state,uint8 flag);
void motion_adjust_right(struct motion_state* m_state,uint8 flag);
void motion_stop(struct motion_state* m_state,uint8 flag);
