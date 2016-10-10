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
#include <stdint.h>
//#include "project.h"
#include "Astar.h"



#define MAP_WIDTH 19
#define MAP_HEIGHT 15

int16_t find_path(uint8_t level, int *map, uint16_t *route, uint16_t start, uint16_t destination);

uint8_t next_turn(int16_t *route, uint16_t x, uint16_t y, uint16_t angle);







#endif

 /* [] END OF FILE */