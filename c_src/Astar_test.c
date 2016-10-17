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

#include <stdio.h>
#include <stdlib.h>
#include "Astar.h"
#include "pathfind.h"
#include "map.h"
#include "defines.h"
#include "dfs_traverse.h"


struct State;

struct State{
   	// int16_t *route;
   	uint8_t level;
   	int16_t steps;
   	int16_t count;
   	int16_t step_counter;
   	uint8_t food_index;
   	// data_main *rf_data;
};

int in_sett(int16_t *route, int steps, int node){
	int i;

	for (i = 0; i < steps; i++){
		if (*(route + i) == node){
			return 1;
		}
	}

	return 0;
}

int main(void){
	int* mapp;
	int16_t* route;
	int i,j;
	uint16_t steps = 0;
	printf("\n================================================= start\n\n");

	route = (int16_t*)malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(short));

	//steps = astar(map, MAP_WIDTH, MAP_HEIGHT, route, 1*MAP_WIDTH+1, 13*MAP_WIDTH+17);
	// steps = find_path(2, map, route, 63, 380, food_packets[2][0], food_packets[2][1]);
	steps = find_path(1, map, route, 63, 361, food_packets[2][0], food_packets[2][1]);
	//free(a);

	printf("\n======================== ASTAR end\n");

	printf("TOTAL STEPS = %d\n", steps);

	for (i = 0; i < 15; i++){
		for (j = 0; j < 19; j++){
			if (in_sett(route, steps, i*MAP_WIDTH+j)){
				printf("%c", 'o');
			} else if (map[i][j] == 1){
				printf("%c", '#');
			} else {
				printf("%c", ' ');
			}
		}
		printf("\n");
	}

	struct State cs;
	cs.step_counter = 0;

	struct State * cs_p = &cs;


	int16_t x = 173;
	int16_t y = 363;
	int16_t angl = 0;
	int16_t counter = 0;
	int16_t *counter_p = &counter;
	decision_type decision = STRAIGHT;
//	decision_type decision = next_turn(route, steps, x, y, angl, counter_p);
	int16_t decision_v = turn_around(route, steps, x, y, angl, &(cs_p->step_counter));
	printf("TURN AROUND VALUE = %i\n", decision_v);
	decision_v = turn_around(route, steps, x+2, y, angl, counter_p);
	printf("TURN AROUND VALUE = %i\n", decision_v);

	if (decision == STRAIGHT){
		printf("decision = STRAIGHT\n");
	}

	if (decision == TURN_LEFT){
		printf("decision = TURN_LEFT\n");
	}

	if (decision == TURN_RIGHT){
		printf("decision = TURN_RIGHT\n");
	}

	if (decision == TURN_AROUND){
		printf("decision = TURN_AROUND\n");
	}

	if (decision == OUT_OF_BOUNDS){
		printf("decision = OUT_OF_BOUNDS\n");
	}

	printf("TURN AROUND VALUE = %i\n", decision_v);

	printf("ENUM SIZE = %i\n", sizeof(astar_status));

	free(route);
	return 0;
}














/* [] END OF FILE */
