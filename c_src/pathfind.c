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
#include "project.h"
 
static int16_t next_node_angle(int16_t *route, int16_t current);
static decision_type turn_decision(int16_t current_angle, int16_t next_angle);
static void add_ghost_costs(int16_t *addi_cost, int16_t *ghosts);


int16_t find_path(uint8_t level, int16_t map[15][19], int16_t *route, int16_t start_x, int16_t start_y, int16_t dest_x, int16_t dest_y){

	int16_t start = conv_location(start_x, start_y, -1);
	int16_t destination = dest_y * MAP_WIDTH + dest_x;
	int16_t *addi_cost = calloc(MAP_WIDTH*MAP_HEIGHT, sizeof(int16_t));
	int16_t steps;

	#ifdef SIMULATION_H
		printf("FIND_PATH START = %i\n", start);
		printf("FIND_PATH DEST  = %i\n", destination);
	#endif
	
	if (level == 1){
		steps = dfs_traverse(route, start);;
	} else if (level == 2){
		steps = astar(map, addi_cost, route, start, destination);
	} else if (level == 3){
        steps = astar(map, addi_cost, route, start, destination);
	}


	return steps;
}

int16_t find_path_ghost(uint8_t level, int16_t map[15][19], int16_t *route, 
						int16_t start_x, int16_t start_y, int16_t dest_node_x, int16_t dest_node_y,
						uint16_t g1_x, uint16_t g1_y,
						uint16_t g2_x, uint16_t g2_y,
						uint16_t g3_x, uint16_t g3_y)
{
	int16_t steps = 0;
	int16_t start = conv_location(start_x, start_y, -1);
	int16_t destination = dest_node_y * MAP_WIDTH + dest_node_x;
	int16_t *addi_cost = calloc(MAP_WIDTH*MAP_HEIGHT, sizeof(int16_t));
	int16_t ghosts[3];


	ghosts[0] = conv_location(g1_x, g1_y, -1);
	ghosts[1] = conv_location(g2_x, g2_y, -1);
	ghosts[2] = conv_location(g3_x, g3_y, -1);

	add_ghost_costs(addi_cost, ghosts);

	steps = astar(map, addi_cost, route, start, destination);

	free(addi_cost);
	
	// free(ghosts);
	return steps;
}

decision_type next_turn(int16_t *route, int16_t steps, int16_t x, int16_t y, int16_t angle, int16_t *counter){
	int16_t current = conv_location(x, y, round_angle(angle/10));
	int16_t i, temp, next_direction, current_direction;	//next direction => 0=north, 1=south, 2=east, 3=west
	uint8_t in_bound = 0;

	// printf("next_turn: current before = %i (%i, %i)\n", current, current%MAP_WIDTH, current/MAP_WIDTH);

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
			// *counter = i;
			break;
		}
	}

	if (in_bound == 0){
		return OUT_OF_BOUNDS;
	} else if (current == steps - 1){
		return ARRIVED;
	}

	// printf("next_turn: current after = %i (%i, %i)\n", current, current%MAP_WIDTH, current/MAP_WIDTH);
	// printf("next y = %i\n", *(route + current + 1)/MAP_WIDTH);

	next_direction = next_node_angle(route, current);

	current_direction = round_angle(angle/10);

	#ifdef SIMULATION_H
		printf("CURRENT ANGLE = %i\n", current_direction);
		printf("REL_ANGLE = %i\n", next_direction);
	#endif

	return turn_decision(current_direction, next_direction);
}

int16_t turn_around(int16_t *route, int16_t steps, int16_t x, int16_t y, int16_t angle, int16_t *counter){
	int16_t current = conv_location(x, y, -1);
	int16_t i, temp, next_direction, current_direction;	//next direction => 0=north, 1=south, =east, 3=west

	printf("next_turn: current before = %i (%i, %i)\n", current, current%MAP_WIDTH, current/MAP_WIDTH);

	temp = (counter == 0)? 0 : *counter;

	for (i = temp; i < steps; i++){
		if (*(route + i) == current){
			current = i;
			break;
		}
	}

	current_direction = round_angle(angle/10);

	printf("next_turn: current after = %i (route = %i)\n", current, *(route+current));
	// printf("next y = %i\n", *(route + current + 1)/MAP_WIDTH);

	next_direction = next_node_angle(route, current);

	if(abs(current_direction - next_direction) == 180){
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

	current_node = calc_current_node(*prev_node, get_distance(), *angle);

	#ifdef SIMULATION_H
		printf("dfs_next: prev_node = %i, current node = %i\n", *prev_node, current_node);
	#endif

	temp = (counter == 0)? 0 : *counter;

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

	next_direction = next_node_angle(route, current_index);

	#ifdef SIMULATION_H
		printf("next_turn: current after = %i (%i, %i)\n", current_index, current_index%MAP_WIDTH, current_index/MAP_WIDTH);
		printf("CURRENT ANGLE = %i\n", *angle);
		printf("REL_ANGLE = %i\n", next_direction);
	#endif

	*prev_node = current_node;

	if(abs(*angle - next_direction) == 180){
		*angle = (*angle + 180)%360;
		return TURN_AROUND;

	} else if (*angle == 0 && next_direction == 270){
		*angle = (*angle + 270)%360;
		return TURN_RIGHT;

	} else if (*angle == 270 && next_direction == 0){
		*angle = (*angle + 90)%360;
		return TURN_LEFT;

	} else if (*angle == next_direction){
		return STRAIGHT;

	} else if (*angle > next_direction){
		*angle = (*angle + 270)%360;
		return TURN_RIGHT;

	} else if (*angle < next_direction){
		*angle = (*angle + 90)%360;
		return TURN_LEFT;

	} else {
		return STOP;
	}
}

int16_t dfs_turn_around(int16_t *route, int16_t steps, int16_t *prev_node, int16_t *angle, int16_t *counter){
	int16_t i, temp, current_index = 0, current_node, next_direction;

	current_node = calc_current_node(*prev_node, get_distance(), *angle);

	#ifdef SIMULATION_H
		printf("dfs_next: prev_node = %i, current node = %i\n", *prev_node, current_node);
	#endif

	temp = (counter == 0)? 0 : *counter;

	for (i = temp; i < steps; i++){
		if (*(route + i) == current_node){
			current_index = i;
			break;
		}
	}

	next_direction = next_node_angle(route, current_index);

	#ifdef SIMULATION_H
		printf("next_turn: current after = %i (%i, %i)\n", current_index, current_index%MAP_WIDTH, current_index/MAP_WIDTH);
		printf("CURRENT ANGLE = %i\n", *angle);
		printf("REL_ANGLE = %i\n", next_direction);
	#endif

	if(abs(*angle - next_direction) == 180){
		*prev_node = current_node;
		*counter = i;
		*angle = (*angle + 180)%360;
		return 1;
	} else {
		return 0;
	}

}


int16_t conv_location(int16_t x, int16_t y, int16_t angle){
	int16_t x_out, y_out;
	float x_f, x_decimal;
	float y_f, y_decimal;

	x_f = (float)x/MAP_WIDTH_PIXEL * MAP_WIDTH;
	y_f = (float)y/MAP_HEIGHT_PIXEL * MAP_HEIGHT;

//	 East
	 if (angle == 0){
	 	x_f += HOZ_OFFSET;

	 // North
	 } else if (angle == 90){
	 	y_f -= VER_OFFSET;

	 // West
	 } else if (angle == 180){
	 	x_f -= HOZ_OFFSET;

	 // South
	 } else if (angle == 270){
	 	y_f += VER_OFFSET;
	 }

	x_decimal = x_f - (int16_t)x_f;
	y_decimal = y_f - (int16_t)y_f;

	if (x_decimal > 0.9){
		x_out = (int16_t)x_f + 1;
	} else {
		x_out = (int16_t)x_f;
	}

	if (y_decimal > 0.92){
		y_out = (int16_t)y_f + 1;
	} else {
		y_out = (int16_t)y_f;
	}

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
	int16_t current = conv_location(current_x, current_y, -1);
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

static int16_t next_node_angle(int16_t *route, int16_t current){
	if (*(route + current + 1)/MAP_WIDTH < *(route + current)/MAP_WIDTH){	//North
		return 90;
	} else if (*(route + current + 1)/MAP_WIDTH > *(route + current)/MAP_WIDTH){	//South
		return 270;
	} else if (*(route + current + 1)%MAP_WIDTH > *(route + current)%MAP_WIDTH){	//East
		return 0;
	} else if (*(route + current + 1)%MAP_WIDTH < *(route + current)%MAP_WIDTH){	//West
		return 180;
	} else {
		return -1;
	}
}

static decision_type turn_decision(int16_t current_angle, int16_t next_angle){
	if(abs(current_angle - next_angle) == 180){
		return TURN_AROUND;
	} else if (current_angle == 0 && next_angle == 270){
		return TURN_RIGHT;
	} else if (current_angle == 270 && next_angle == 0){
		return TURN_LEFT;
	} else if (current_angle == next_angle){
		return STRAIGHT;
	} else if (current_angle > next_angle){
		return TURN_RIGHT;
	} else if (current_angle < next_angle){
		return TURN_LEFT;
	} else {
		return STOP;
	}
}

int16_t calc_current_node(int16_t prev_node, int16_t distance, int16_t angle){
	int16_t prev_node_y = prev_node/MAP_WIDTH;

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

	} else {
		return -1;
	}
}

static void add_ghost_costs(int16_t *addi_cost, int16_t *ghosts){
	int16_t temp, i;
	clear_route(addi_cost, MAP_WIDTH*MAP_HEIGHT);

	for (i = 0; i < GHOSTS; i++){
		// At the ghost
		temp = *(ghosts + i);
		if (temp >= 0 && temp < MAP_WIDTH*MAP_HEIGHT){
			*(addi_cost + temp) = GHOST_COST;
		}

		// North of ghost
		temp = *(ghosts + i) - MAP_WIDTH;
		if (temp >= 0 && temp < MAP_WIDTH*MAP_HEIGHT){
			*(addi_cost + temp) = GHOST_COST_SURROUD;
		}
	
		// South of ghost
		temp = *(ghosts + i) + MAP_WIDTH;
		if (temp >= 0 && temp < MAP_WIDTH*MAP_HEIGHT){
			*(addi_cost + temp) = GHOST_COST_SURROUD;
		}

		// West of ghost
		temp = *(ghosts + i) - 1; 
		if (temp >= 0 && temp < MAP_WIDTH*MAP_HEIGHT){
			*(addi_cost + temp) = GHOST_COST_SURROUD;
		}

		temp = *(ghosts + i) + 1;
		if (temp >= 0 && temp < MAP_WIDTH*MAP_HEIGHT){
			*(addi_cost + temp) = GHOST_COST_SURROUD;
		}
	}
}

uint8_t is_vertex(const uint16_t node){
	uint16_t x_cell = node % MAP_WIDTH;
	uint16_t y_cell = node / MAP_WIDTH;

	if(map[x_cell][y_cell] == 1){
		return 0;
	} else{
		if(map[x_cell][y_cell-1] == 0 && map[x_cell][y_cell+1] == 0){
			if(map[x_cell + 1][y_cell] == 0 || map[x_cell - 1][y_cell] == 0){
				return 1;
			}else{
				return 0;
			}
			
		} else if(map[x_cell-1][y_cell] == 0 && map[x_cell+1][y_cell] == 0){
			if(map[x_cell][y_cell + 1] == 0 || map[x_cell][y_cell - 1] == 0){
				return 1;
			}else{
				return 0;
			}
		} else{
			return 1;
		}
	}

	return 0;

}


int16_t get_vertex_list(const int16_t* route, const int16_t steps, int16_t *vertex_list){
	uint16_t i;
    uint16_t v_index = 0;
	for(i = 0; i < steps; i++){
		if(is_vertex(*(route+i))){
			if(!in_set(vertex_list, v_index,*(route+i))){
				*(vertex_list + v_index) = *(route+i);
				v_index++;
			}
		}
	}
	return v_index;
}

int16_t get_vertex_list_length(const int16_t* route, const int16_t steps){
	uint16_t i;
	int16_t v_index = 0;
	for(i = 0; i < steps; i++){
		if(is_vertex(*(route+i))){
			v_index++;
		}
	}
	return v_index;
}

int16_t in_set(const int16_t* array, const uint16_t length, const uint16_t element){
	uint16_t i;
	for(i = 0; i < length; i++){
		if(*(array+i) == element){
			return 1;
		}
	}
	return 0;
}

int16_t get_shortest_vertex(const int16_t* vertex_list,int16_t *route,const int16_t list_length,const int16_t current_node){
	int16_t i;
	int16_t steps;
	int16_t min_steps = 999;
	int16_t current_vertex;
	int16_t start_x = current_node % MAP_WIDTH; 
	int16_t start_y = current_node / MAP_WIDTH;
	int16_t dest_x; 
	int16_t dest_y; 
	for(i = 0; i < list_length ; i++){
		if(*(vertex_list + i) != -1){
			dest_x = *(vertex_list + i) % MAP_WIDTH;
			dest_y = *(vertex_list + i) / MAP_WIDTH;
			steps = find_path(2,map, route,start_x,start_y, dest_x,dest_y);
			if(steps < min_steps){
				min_steps = steps;
				current_vertex = *(vertex_list+i);
			}
		}
	}
	return current_vertex;
}


/* [] END OF FILE */
