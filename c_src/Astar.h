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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>

#define MAP_WIDTH 19
#define MAP_HEIGHT 15

#define TRACK 0
#define WALL 1




typedef enum {UNKNOWN, OPEN, CLOSED} astar_status;

int16_t astar(int16_t map[15][19], int16_t *addi_cost, int16_t *route, int16_t start, int16_t destination);

// static void init_astar(int16_t *open, int16_t *closed, int16_t *parent, int16_t *g_cost, int16_t size);

// static uint8_t is_empty(int16_t *list, int16_t size);

// static int16_t next_current(int16_t *open, int16_t *g_cost, int16_t destination, int16_t size);

// static void add_closed(int16_t *closed, int16_t location);

// static uint8_t add_open(int16_t *map, int16_t *open, int16_t *closed, int16_t *g_cost, int16_t *parent, int16_t current);

// static uint8_t traceback(int16_t *parent, int16_t *traceback, int16_t destination, int16_t start);

// static void flip_array(int16_t *source, int16_t *target, int16_t size);

// static int16_t manhattan(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif

 /* [] END OF FILE */