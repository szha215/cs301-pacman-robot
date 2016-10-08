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
	printf("start\n");

	route = malloc(285 * sizeof(short));

	steps = astar(map, route, 2, 6);
	//free(a);

	printf("manhattan = %i\n", manhattan(6,4,4,14));
	printf("========================end\n");

	return 0;
}














/* [] END OF FILE */
