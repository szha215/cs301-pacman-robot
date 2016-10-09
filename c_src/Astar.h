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


#ifndef ASTAR_H
#define ASTAR_H

#include <math.h>
#include <limits.h>

#define MAP_WIDTH 19
#define MAP_HEIGHT 15

#define TRACK 0
#define WALL 1

#define uint8 short

typedef enum {UNKNOWN, VISITED, EXPLORED} status;

short astar(int *map, short width, short height, short *route, short start, short destination);

static void init_astar(short *open, short *closed, short *parent, short *g_cost, short size);

static uint8 is_empty(short *list, short size);

static uint8 in_set(short* array, short data);

static short next_current(short *open, short *g_cost, short destination, short size);

static void add_closed(short *closed, short location);



static short manhattan(uint8 x1, uint8 y1, uint8 x2, uint8 y2);

#endif

 /* [] END OF FILE */