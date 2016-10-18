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

// static int16_t dist_to_nodes(int16_t distance, int16_t angle);

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
		//LED_Write(1);
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

	if (in_bound == 0){
		//LED_Write(~LED_Read());
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
	int16_t i, temp, rel_direction, current_direction;	//next direction => 0=north, 1=south, =east, 3=west

	printf("next_turn: current before = %i (%i, %i)\n", current, current%MAP_WIDTH, current/MAP_WIDTH);

	if (counter == 0){
		temp = 0;
	} else {
		temp = *counter;
	}

	for (i = temp; i < steps; i++){
		if (*(route + i) == current){
			current = i;
			break;
		}
	}

	current_direction = round_angle(angle/10);

	printf("next_turn: current after = %i (route = %i)\n", current, *(route+current));
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
		// LED_Write(1);
		*counter = i;
		return 1;
	} else {
		return 0;

	}
}

decision_type dfs_next_turn(int16_t *route, int16_t steps, int16_t *prev_node, int16_t *angle, int16_t *counter){
	int16_t i, temp, current_index, current_node, next_direction;
	int16_t in_bound = 0;
	decision_type decision;

	current_node = calc_current_node(*prev_node, get_distance(), *angle);
	printf("dfs_next: prev_node = %i, current node = %i\n", *prev_node, current_node);
	if (counter == 0){
		//LED_Write(1);
		temp = 0;
	} else {
		temp = *counter;
	}

	for (i = temp; i < steps; i++){
		if (*(route + i) == current_node){
			current_index = i;
			in_bound = 1;
			*counter = i;
			printf("dfs: CURRENT NODE FOUND at %i\n", i);
			break;
		}
	}

	if (in_bound == 0){
		return TURN_AROUND;
	}


	printf("next_turn: current after = %i (%i, %i)\n", current_index, current_index%MAP_WIDTH, current_index/MAP_WIDTH);
	// printf("next y = %i\n", *(route + current + 1)/MAP_WIDTH);

	if (*(route + current_index + 1)/MAP_WIDTH < *(route + current_index)/MAP_WIDTH){	//North
		next_direction = 90;
	}else if (*(route + current_index + 1)/MAP_WIDTH > *(route + current_index)/MAP_WIDTH){	//South
		next_direction = 270;
	}else if (*(route + current_index + 1)%MAP_WIDTH > *(route + current_index)%MAP_WIDTH){	//East
		next_direction = 0;
	}else if (*(route + current_index + 1)%MAP_WIDTH < *(route + current_index)%MAP_WIDTH){	//West
		next_direction = 180;
	} else {
		// printf("wrong next_direction\n");
	}
	// printf("INPUT ANGLE = %i\n", angle);
	// printf("RELATIVE ANGLE = %i\n", next_direction);

	printf("CURRENT ANGLE = %i\n", *angle);
	printf("REL_ANGLE = %i\n", next_direction);

	*prev_node = current_node;

	if(abs(*angle - next_direction) == 180){
		*angle = (*angle + 180)%360;
		return TURN_AROUND;

	} else if (*angle == 0 && next_direction == 270){
		printf("dfs: angle before = %i\n", *angle);
		*angle = (*angle + 270)%360;
		printf("dfs: angle after = %i\n", *angle);
		return TURN_RIGHT;

	} else if (*angle == 270 && next_direction == 0){
		*angle = (*angle + 90)%360;
		return TURN_LEFT;

	} else if (*angle == next_direction){
		return STRAIGHT;

	} else if (*angle > next_direction){
		printf("dfs: angle before = %i\n", *angle);
		*angle = (*angle + 270)%360;
		printf("dfs: angle after = %i\n", *angle);
		return TURN_RIGHT;

	} else if (*angle < next_direction){
		*angle = (*angle + 90)%360;
		return TURN_LEFT;

	} else {
		return STOP;
	}
}

int16_t dfs_turn_around(int16_t *route, int16_t steps, int16_t *prev_node, int16_t *angle, int16_t *counter){
	int16_t i, temp, current_index, current_node, next_direction;
	decision_type decision;

	current_node = calc_current_node(*prev_node, get_distance(), *angle);
	printf("dfs_next: prev_node = %i, current node = %i\n", *prev_node, current_node);
	if (counter == 0){
		//LED_Write(1);
		temp = 0;
	} else {
		temp = *counter;
	}

	for (i = temp; i < steps; i++){
		if (*(route + i) == current_node){
			current_index = i;
			break;
		}
	}

	printf("next_turn: current after = %i (%i, %i)\n", current_index, current_index%MAP_WIDTH, current_index/MAP_WIDTH);
	// printf("next y = %i\n", *(route + current + 1)/MAP_WIDTH);

	if (*(route + current_index + 1)/MAP_WIDTH < *(route + current_index)/MAP_WIDTH){	//North
		next_direction = 90;
	}else if (*(route + current_index + 1)/MAP_WIDTH > *(route + current_index)/MAP_WIDTH){	//South
		next_direction = 270;
	}else if (*(route + current_index + 1)%MAP_WIDTH > *(route + current_index)%MAP_WIDTH){	//East
		next_direction = 0;
	}else if (*(route + current_index + 1)%MAP_WIDTH < *(route + current_index)%MAP_WIDTH){	//West
		next_direction = 180;
	} else {
		// printf("wrong next_direction\n");
	}
	// printf("INPUT ANGLE = %i\n", angle);
	// printf("RELATIVE ANGLE = %i\n", next_direction);

	printf("CURRENT ANGLE = %i\n", *angle);
	printf("REL_ANGLE = %i\n", next_direction);
	

	if(abs(*angle - next_direction) == 180){
		*prev_node = current_node;
		*counter = i;
		*angle = (*angle + 180)%360;
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

	if (x_decimal > 0.85){
		x_out = (int16_t)x_f + 1;
	} else {
		x_out = (int16_t)x_f;
	}

	if (y_decimal > 0.9){
		y_out = (int16_t)y_f + 1;
	} else {
		y_out = (int16_t)y_f;
	}

	// printf("conv_location = %i, %i\n", ((int16_t)y_f)%MAP_WIDTH, ((int16_t)x_f));

	return (y_out * MAP_WIDTH + x_out);
}

void conv_location_pixel(int16_t x_node, int16_t y_node, int16_t *x_pixel, int16_t *y_pixel){
	float pixel_x = MAP_WIDTH_PIXEL / MAP_WIDTH;
	float pixel_y = MAP_HEIGHT_PIXEL / MAP_HEIGHT;

	*x_pixel = (int16_t)(x_node * pixel_x);
	*y_pixel = (int16_t)(y_node * pixel_y);
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

int16_t calc_current_node(int16_t prev_node, int16_t distance, int16_t angle){
	int16_t prev_node_y = prev_node/MAP_WIDTH;


	// printf("calc_cu: prev_node = %i, distance = %i, angle = %i\n", prev_node, distance, angle);
	if (angle == 0){
		return prev_node + distance/NODE_WIDTH_MM;

	} else if (angle == 180){
		return prev_node - distance/NODE_WIDTH_MM;

	} else if (angle == 90){

		prev_node_y = distance/NODE_WIDTH_MM;
		return prev_node - prev_node_y*MAP_WIDTH;

	} else if (angle == 270){
		prev_node_y = distance/NODE_WIDTH_MM;
		return prev_node + prev_node_y*MAP_WIDTH;
	}
}



/* [] END OF FILE */
