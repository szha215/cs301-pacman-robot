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

#ifndef A_STAR_H
#define A_STAR_H


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "map.h"

#define MAP_WIDTH 19
#define MAP_HEIGHT 15

#define TRACK 0
#define WALL 1


#define OPEN 1
#define CLOSED 2

int16_t a_star(int16_t *map, int16_t *addi_cost, int16_t *route, int16_t start, int16_t destination);



#endif
