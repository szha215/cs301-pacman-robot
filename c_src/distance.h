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

#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
#include "defines.h"
// #include "simulation.h"
#ifndef SIMULATION_H
	#include "project.h"
#endif

#define WHEEL_CIRCUMFERENCE_MM 204
#define COUNTS_PER_REVOLUTION 57
#define QUAD_TO_MM_RATIO 3.58	// = circumference/counts per revolution, pre calculated
#define NODE_WIDTH_MM 135
#define NODE_HEIGHT_MM 130

#define LOWER_THRESHOLD
#define UPPER_THRESHOLD

int16_t get_distance();
void clear_quad();


#endif