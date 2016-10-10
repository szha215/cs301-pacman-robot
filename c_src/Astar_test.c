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
#include "map.h"

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
	int* route;
	int i,j;
	uint8_t steps = 0;
	printf("\n================================================= start\n\n");

	route = malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(short));

	steps = astar(map, MAP_WIDTH, MAP_HEIGHT, route, 1*MAP_WIDTH+1, 13*MAP_WIDTH+17);
	//free(a);

	printf("\n======================== ASTAR end\n");

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


	free(route);
	return 0;
}














/* [] END OF FILE */
