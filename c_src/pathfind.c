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

#include "pathfind.h"

int16_t find_path(uint8_t level, int *map, uint16_t *route, uint16_t start, uint16_t destination){
	if (level == 1){

	} else if (level == 2){
		return astar(map, MAP_WIDTH, MAP_HEIGHT, route, start, destination);
	} else if (level == 3){

	}

	return -1;
}

uint8_t next_turn(int16_t *route, int16_t steps, uint16_t x, uint16_t y, uint16_t angle){
	int16_t current = y * MAP_WIDTH + x;
	int16_t i, rel_direction;	//next direction => 0=north, 1=south, 2=east, 3=west
	int16_t current_step = -1;

	for (i = 0; i < steps; i++){
		if (*(route + i) == current){
			current_step = i;
			break;
		}
	}

	if (current_step == -1){
		return current_step;
	}

	if (*(route + current_step + 1)/MAP_WIDTH < *(route + current_step)/MAP_WIDTH){	//North
		rel_direction = 0;
	}else if (*(route + current_step + 1)/MAP_WIDTH > *(route + current_step)/MAP_WIDTH){	//South
		rel_direction = 1;
	}else if (*(route + current_step + 1)%MAP_WIDTH > *(route + current_step)%MAP_WIDTH){	//East
		rel_direction = 2;
	}else if (*(route + current_step + 1)%MAP_WIDTH < *(route + current_step)%MAP_WIDTH){	//West
		rel_direction = 3;
	}

}










/* [] END OF FILE */
