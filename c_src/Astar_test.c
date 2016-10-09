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

int main(void){
	int* mapp;
	int* route;
	uint8 steps = 0;
	printf("\n================================================= start\n\n");

	route = malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(short));

	steps = astar(map, MAP_WIDTH, MAP_HEIGHT, route, 146, 6);
	//free(a);

	printf("\n======================== end\n");




	free(route);
	return 0;
}














/* [] END OF FILE */
