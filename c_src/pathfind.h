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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "simulation.h"
#ifndef SIMULATION_H
	#include "project.h"
#endif
#include "a_star.h"

#include "dfs_traverse.h"
#include "defines.h"
#include "distance.h"




#define MAP_WIDTH 19
#define MAP_HEIGHT 15

#define MAP_WIDTH_PIXEL 1024.0
#define MAP_HEIGHT_PIXEL 768.0

int16_t find_path(uint8_t level, int16_t map[15][19], int16_t *route, int16_t start_x, int16_t start_y, int16_t dest_node_x, int16_t dest_node_y);
int16_t find_path_ghost(uint8_t level, int16_t map[15][19], int16_t *route, int16_t start_x, int16_t start_y, int16_t dest_node_x, int16_t dest_node_y);

decision_type next_turn(int16_t *route, int16_t steps, int16_t x, int16_t y, int16_t angle, int16_t* counter);
decision_type dfs_next_turn(int16_t *route, int16_t steps, int16_t *prev_node, int16_t *angle, int16_t *counter);

int16_t turn_around(int16_t *route, int16_t steps, int16_t x, int16_t y, int16_t angle, int16_t *counter);
int16_t dfs_turn_around(int16_t *route, int16_t steps, int16_t *prev_node, int16_t *angle, int16_t *counter);

int16_t conv_location(int16_t x, int16_t y);

void clear_route(int16_t *route, int16_t steps);

int8_t are_we_there_yet(int16_t current_x, int16_t current_y, int16_t dest_x, int16_t dest_y);
int16_t round_angle(int16_t angle);
int16_t turn_around(int16_t *route, int16_t steps, int16_t x, int16_t y, int16_t angle, int16_t *counter);

int16_t calc_current_node(int16_t prev_node, int16_t distance, int16_t angle);


#endif

 /* [] END OF FILE */