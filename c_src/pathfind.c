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

int16_t find_path(uint8_t level, int *map, int16_t *route, int16_t start_x, int16_t start_y, int16_t dest_x, int16_t dest_y){

	int16_t start = conv_location(start_x, start_y);
	int16_t destination = conv_location(dest_x, dest_y);

	if (level == 1){

	} else if (level == 2){
		return astar(map, MAP_WIDTH, MAP_HEIGHT, route, start, destination);
	} else if (level == 3){

	}

	return -1;
}

decision_type next_turn(int16_t *route, int16_t steps, int16_t x, int16_t y, int16_t angle){
	int16_t current = conv_location(x, y);
	int16_t i, rel_direction, current_direction;	//next direction => 0=north, 1=south, 2=east, 3=west
	

	for (i = 0; i < steps; i++){
		if (*(route + i) == current){
			current = i;
			break;
		}
	}

	if (current == -1){
		return STOP;
	}

	if (*(route + current + 1)/MAP_WIDTH < *(route + current)/MAP_WIDTH){	//North
		rel_direction = 90;
	}else if (*(route + current + 1)/MAP_WIDTH > *(route + current)/MAP_WIDTH){	//South
		rel_direction = 270;
	}else if (*(route + current + 1)%MAP_WIDTH > *(route + current)%MAP_WIDTH){	//East
		rel_direction = 0;
	}else if (*(route + current + 1)%MAP_WIDTH < *(route + current)%MAP_WIDTH){	//West
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

int16_t conv_location(int16_t x, int16_t y){
	float x_f = x/MAP_HEIGHT_PIXEL * MAP_WIDTH;
	float y_f = y/MAP_HEIGHT_PIXEL * MAP_HEIGHT;

	return ((int16_t)y_f) * MAP_WIDTH + ((int16_t)x_f/MAP_WIDTH_PIXEL);
}

void clear_route(int16_t *route, int16_t steps){
	int16_t i;

	for (i = 0; i < steps; i++){
		*(route + i) = 0;
	}
}

int8_t are_we_there_yet(int16_t current_x, int16_t current_y, int16_t dest_x, int16_t dest_y){
	int16_t current = conv_location(current_x, current_y);
	int16_t destination = conv_location(dest_x, dest_y);

	if (current == destination){
		return 1;
	}

	return 0;
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
