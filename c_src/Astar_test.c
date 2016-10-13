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
	steps = find_path(1, map, route, 63, 380, 55, 155);
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

	int16_t x = 164;
	int16_t y = 269;

	decision_type decision = next_turn(route, steps, x, y, 50);

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

	printf("ENUM SIZE = %i\n", sizeof(astar_status));

	free(route);
	return 0;
}














/* [] END OF FILE */
