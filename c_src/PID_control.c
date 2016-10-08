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

#include "PID_control.h"

void pid_calc_output(pid_params *params,uint16 current_val){
	params->measured_val = current_val;
	params->error = params->set_val - params->measured_val;
	params->integral += params->error * params->dt;
	params->derivative = (params->error - params->prev_error)/params->dt;
	params->output = params->K_p * params->error + K_i * params->integral + K_d * params->derivative;
	params->prev_error = params->error;
}

void pid_calc_p_output(pid_params *params,uint16 current_val){
	params->measured_val = current_val;
	params->error = params->set_val - params->measured_val;
    params->integral += params->error * params->dt;
    params->derivative = (params->error - params->prev_error)/params->dt;
    params->prev_error = params->error;
	params->p_output = params->K_p * params->error + K_i * params->integral + K_d * params->derivative;
}


pid_params *pid_init(float dt,uint16 set_val){
	pid_params *params = malloc(sizeof(pid_params));
	params->dt = dt;
	params->set_val = set_val;
	params->error = 0;


	params->K_p = 1.00 / set_val;
	params->prev_error = 0;
	params->integral = 0;
	params->derivative = 0;
	params->output = 0;
	params->p_output = 0;
	params->measured_val = 0;
	return params;
}

void pid_set_desired_val(pid_params *params, uint16 set_val){
	params->set_val = set_val;
	params->K_p = 1.00 / set_val;
	
}

void free_pid_mem(pid_params *params){
	free(params);
}


/* [] END OF FILE */