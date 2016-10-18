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

#include "distance.h"





int16_t get_distance(){
	int16_t quad_avg;

	#ifndef SIMULATION_H
		quad_avg = (QuadDec_M1_GetCounter() + QuadDec_M2_GetCounter()) / 2;
		LED_Write(1);
		return quad_avg * QUAD_TO_MM_RATIO;

	#else
		return 135;	
	#endif
}



void clear_quad(){
	#ifndef SIMULATION_H
		QuadDec_M1_SetCounter(0);
		QuadDec_M2_SetCounter(0);
	#endif
}



