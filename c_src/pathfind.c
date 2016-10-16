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

int16_t find_path(uint8_t level, int16_t map[15][19], int16_t *route, int16_t start_x, int16_t start_y, int16_t dest_x, int16_t dest_y){

	int16_t start = conv_location(start_x, start_y);
	int16_t destination = dest_y * MAP_WIDTH + dest_x;

	printf("FIND_PATH START = %i\n", start);
	printf("FIND_PATH DEST  = %i\n", destination);
	
	if (level == 1){
		return dfs_traverse(route, start);
	} else if (level == 2){
		return astar(map, MAP_WIDTH, MAP_HEIGHT, route, start, destination);
	} else if (level == 3){

	}

	return -5;
}

decision_type next_turn(int16_t *route, int16_t steps, int16_t x, int16_t y, int16_t angle, int16_t *counter){
	int16_t current = conv_location(x, y);
	int16_t i, temp, rel_direction, current_direction;	//next direction => 0=north, 1=south, 2=east, 3=west
	uint8_t in_bound = 0;

	printf("next_turn: current before = %i (%i, %i)\n", current, current%MAP_WIDTH, current/MAP_WIDTH);

	if (counter == 0){
		temp = 0;
	} else {
		temp = *counter;
	}

	for (i = temp; i < steps; i++){
		if (*(route + i) == current){
			current = i;
			in_bound = 1;
			*counter = i;
			break;
		}
	}
printf("TEST\n");
	if (in_bound == 0){
	
		return OUT_OF_BOUNDS;
	}

	printf("next_turn: current after = %i (%i, %i)\n", current, current%MAP_WIDTH, current/MAP_WIDTH);
	// printf("next y = %i\n", *(route + current + 1)/MAP_WIDTH);

	if (*(route + current + 1)/MAP_WIDTH < *(route + current)/MAP_WIDTH){	//North
		rel_direction = 90;
	}else if (*(route + current + 1)/MAP_WIDTH > *(route + current)/MAP_WIDTH){	//South
		rel_direction = 270;
	}else if (*(route + current + 1)%MAP_WIDTH > *(route + current)%MAP_WIDTH){	//East
		rel_direction = 0;
	}else if (*(route + current + 1)%MAP_WIDTH < *(route + current)%MAP_WIDTH){	//West
		rel_direction = 180;
	} else {
		// printf("wrong rel_direction\n");
	}
	// printf("INPUT ANGLE = %i\n", angle);
	// printf("RELATIVE ANGLE = %i\n", rel_direction);

	current_direction = round_angle(angle/10);

	printf("CURRENT ANGLE = %i\n", current_direction);
	printf("REL_ANGLE = %i\n", rel_direction);

	if(abs(current_direction - rel_direction) == 180){
		return TURN_AROUND;
	} else if (current_direction == 0 && rel_direction == 270){
		return TURN_RIGHT;
	} else if (current_direction == 270 && rel_direction == 0){
		return TURN_LEFT;
	} else if (current_direction == rel_direction){
		return STRAIGHT;
	} else if (current_direction > rel_direction){
		return TURN_RIGHT;
	} else if (current_direction < rel_direction){
		return TURN_LEFT;
	} else {
		return STOP;
	}

}

int16_t turn_around(int16_t *route, int16_t steps, int16_t x, int16_t y, int16_t angle, int16_t *counter){
	int16_t current = conv_location(x, y);
	int16_t i, temp, rel_direction, current_direction;	//next direction => 0=north, 1=south, 2=east, 3=west

	printf("next_turn: current before = %i (%i, %i)\n", current, current%MAP_WIDTH, current/MAP_WIDTH);

	if (counter == 0){
		temp = 0;
	} else {
		temp = *counter;
	}

	for (i = temp; i < steps; i++){
		if (*(route + i) == current){
			current = i;
			*counter = i;
			break;
		}
	}

	//printf("next_turn: current after = %i (%i, %i)\n", current, current%MAP_WIDTH, current/MAP_WIDTH);
	// printf("next y = %i\n", *(route + current + 1)/MAP_WIDTH);

	if (*(route + current + 1)/MAP_WIDTH < *(route + current)/MAP_WIDTH){	//North
		rel_direction = 90;
	}else if (*(route + current + 1)/MAP_WIDTH > *(route + current)/MAP_WIDTH){	//South
		rel_direction = 270;
	}else if (*(route + current + 1)%MAP_WIDTH > *(route + current)%MAP_WIDTH){	//East
		rel_direction = 0;
	}else if (*(route + current + 1)%MAP_WIDTH < *(route + current)%MAP_WIDTH){	//West
		rel_direction = 180;
	} else {
		// printf("wrong rel_direction\n");
	}

	if(abs(current_direction - rel_direction) == 180){
		return 1;
	} else {
		return 0;
	}
}

int16_t conv_location(int16_t x, int16_t y){
	int16_t x_out, y_out;
	float x_f, x_decimal;
	float y_f, y_decimal;

	x_f = (float)x/MAP_WIDTH_PIXEL * MAP_WIDTH;
	y_f = (float)y/MAP_HEIGHT_PIXEL * MAP_HEIGHT;

	x_decimal = x_f - (int16_t)x_f;
	y_decimal = y_f - (int16_t)y_f;

	if (x_decimal > 0.8){
		x_out = (int16_t)x_f + 1;
	} else {
		x_out = (int16_t)x_f;
	}

	if (y_decimal > 0.8){
		y_out = (int16_t)y_f + 1;
	} else {
		y_out = (int16_t)y_f;
	}

	// printf("conv_location = %i, %i\n", ((int16_t)y_f)%MAP_WIDTH, ((int16_t)x_f));

	return (y_out * MAP_WIDTH + x_out);
}

void clear_route(int16_t *route, int16_t steps){
	memset(route, 0, steps * sizeof(int16_t));
}

int8_t are_we_there_yet(int16_t current_x, int16_t current_y, int16_t dest_x, int16_t dest_y){
	int16_t current = conv_location(current_x, current_y);
	int16_t destination = dest_y * MAP_WIDTH + dest_x;
	if (dest_x == -1){
		return 0;
	} else if (current == destination){
		return 1;
	}

	return 0;
}

int16_t round_angle(int16_t angle){
	if (angle < 20 || angle > 340){
		return 0;
	} else if (angle < 110 && angle > 70){
		return 90;
	} else if (angle < 200 && angle > 160){
		return 180;
	} else {
		return 270;
	}
}








/* [] END OF FILE */
