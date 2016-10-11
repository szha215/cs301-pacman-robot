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

decision_type next_turn(int16_t *route, uint16_t steps, uint16_t x, uint16_t y, uint16_t angle){
	int16_t current = conv_location(x, y);
	int16_t i, rel_direction, current_direction;	//next direction => 0=north, 1=south, 2=east, 3=west
	int16_t current_step = -1;
	

	for (i = 0; i < steps; i++){
		if (*(route + i) == current){
			current_step = i;
			break;
		}
	}

	if (current_step == -1){
		return STOP;
	}

	if (*(route + current_step + 1)/MAP_WIDTH < *(route + current_step)/MAP_WIDTH){	//North
		rel_direction = 90;
	}else if (*(route + current_step + 1)/MAP_WIDTH > *(route + current_step)/MAP_WIDTH){	//South
		rel_direction = 270;
	}else if (*(route + current_step + 1)%MAP_WIDTH > *(route + current_step)%MAP_WIDTH){	//East
		rel_direction = 0;
	}else if (*(route + current_step + 1)%MAP_WIDTH < *(route + current_step)%MAP_WIDTH){	//West
		rel_direction = 180;
	}

	current_direction = round_angle(angle/10);

	if (current_direction == rel_direction){
		return STRAIGHT;
	} else if (current_direction > rel_direction){
		return TURN_RIGHT;
	} else if (current_direction < rel_direction){
		return TURN_LEFT;
	} else {
		return TURN_AROUND;
	}

}

int16_t conv_location(uint16_t x, uint16_t y){
	float x_f = x/MAP_HEIGHT_PIXEL * MAP_WIDTH;
	float y_f = y/MAP_HEIGHT_PIXEL * MAP_HEIGHT;

	return ((int16_t)y_f) * MAP_WIDTH + ((int16_t)x_f/MAP_WIDTH_PIXEL);
}

static int16_t round_angle(int16_t angle){
	if (angle < 10 && angle > 350){
		return 0;
	} else if (angle < 100 && angle > 80){
		return 90;
	} else if (angle < 190 && angle > 170){
		return 180;
	} else {
		return 270;
	}
}








/* [] END OF FILE */
