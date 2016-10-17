


/* ========================================
 *
 * Copyright GROUP7, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "project.h"
#include "PID_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <tgmath.h>


#define DESIRED_DISTANCE 100 //cm
#define DESIRED_SPEED 15 //cm/s

#define DESIRED_COUNT 20
#define BASE_INCREMENT 10


#define WHEEL_DIAMETER 64	//mm
#define COUNTS_PER_REV 57	
#define COUNT_MODE 4		//4x


#define M_TO_PX_RATIO 415


#define STOP_MOTOR 128
#define M_FORWARD_MAX 255
#define M_BACKWARD_MAX 0

#define M1_FORWARD 158
#define M2_FORWARD 163

    
    


#define M1_FORWARD_SLOW 156
#define M2_FORWARD_SLOW 160

#define M1_BACKWARD 91
#define M2_BACKWARD 88
uint8 cmp_val_m1;
uint8 cmp_val_m2;
pid_params* pid_controller_m1;
pid_params* pid_controller_m2;



 

static volatile uint8 quad_dec_done;
    
    
    
typedef  struct motor_params{
    uint16 distance_travelled;
    uint16 quad_count_m1;
    uint16 quad_count_m2;
}motor_params;
motor_params* motor_parameters;

// typedef struct quad_params{
	int16 quad_dec_m1_total;
	int16 quad_dec_m2_total;
	
    int16 quad_dec_m1_prev;
	int16 quad_dec_m2_prev;

	int16 quad_dec_m1_diff;
	int16 quad_dec_m2_diff;
// }quad_params;

//quad_params* quad_parameters;

void init_motor_control();
motor_params* init_motor_params(uint8 predef_velocity, uint16 predef_distance);
//quad_params* init_quad_params();
uint8 conv_velocity(uint8 velocity);
uint16 conv_distance(uint16 distance);
uint16 conv_counts(uint16 counts);
uint16 conv_pix_distance(uint16 distance);

// stop both
void m_stop();

// both wheels straight
void m_straight();
void m_straight_pid();
void m_straight_slow();

// one wheel slow forward, one wheel forward
void m_adjust_left();
void m_adjust_right();
void rf_adjust_left();
void rf_adjust_right();
// one wheel backward, one wheel forward
void m_turn_left();
void m_turn_right();

void set_quad_dec(int16 quad_m1, int16 quad_m2);

int16 get_quad_dec_m1();

int16 get_quad_dec_m2();

uint8 get_quad_dec_flag();
void set_quad_dec_flag(uint8 flag);

void init_motor_pos(uint16 init_xpos,uint16 init_ypos);

#endif

/* [] END OF FILE */
