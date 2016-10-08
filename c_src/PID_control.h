

/* ========================================
 *
 * GROUP 7
 *
 * Header file for PID controller 
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef PID_CONTROL_H
#define PID_CONTROL_H
#include <stdio.h>
#include <stdlib.h>

#include "project.h"

#define K_i 0.05
#define K_d 0//0.0000035
#define extra_k_p 0//0.00001
#define INTEGRAL_DECAY 0.8
#define TOLERANCE 10

typedef struct pid_params{
    uint16 set_val;
	uint16 error;
	uint16 prev_error;
	uint16 integral;
	uint16 derivative;
	uint8 min;
	uint8 max;
	float output;
	float p_output;
	float i_output;
	float d_output;
	float K_p;
	uint16 measured_val;
    float dt;
	}pid_params;

pid_params *pid_init(float dt,uint16 set_val);

void pid_set_desired_val(pid_params *params, uint16 set_val);

void free_pid_mem(pid_params *params);

void pid_calc_output(pid_params *params,uint16 current_val);


#endif

/* [] END OF FILE */
