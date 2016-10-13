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

int16_t astar(int8_t *map, int16_t width, int16_t height, int8_t *route, int16_t start, int16_t destination);

static void init_astar();

static uint8_t is_empty(int8_t *list, int16_t size);

static int16_t next_current(int16_t destination, int16_t size);

static void add_closed( int16_t location);

static uint8_t add_open(int8_t *map, int16_t current);

static uint8_t traceback( int16_t destination, int16_t start);

static void flip_array(int8_t *source, int8_t *target, int16_t size);

static int16_t manhattan(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif

 /* [] END OF FILE */