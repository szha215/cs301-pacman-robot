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


#ifndef PATHFIND_H
#define PATHFIND_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>
//#include "project.h"
#include "Astar.h"
#include "defines.h"




#define MAP_WIDTH 19
#define MAP_HEIGHT 15

#define MAP_WIDTH_PIXEL 1024.0
#define MAP_HEIGHT_PIXEL 768.0

int16_t find_path(uint8_t level, int *map, uint16_t *route, uint16_t start_x, uint16_t start_y, uint16_t dest_x, uint16_t dest_y);

decision_type next_turn(int16_t *route, uint16_t steps, uint16_t x, uint16_t y, uint16_t angle);

int16_t conv_location(uint16_t x, uint16_t y);

void clear_route(int16_t *route, uint16_t steps);

static int16_t round_angle(int16_t angle);





#endif

 /* [] END OF FILE */