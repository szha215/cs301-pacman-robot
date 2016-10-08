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

#include "Astar.h"

uint8 astar(int *map, short *route, short start, short destination){
	short width = 19;
	short *open, *closed, *parent, *g_cost;
	short o_count, c_count, p_count;
	short current;
	int i, j;

	printf("size of map = %i\n", sizeof(map[0]));
	parent = (short*)malloc(285 * sizeof(short));
	open = (short*)malloc(285 * sizeof(short));
	closed = (short*)malloc(285 * sizeof(short));
	g_cost = (short*)malloc(285 * sizeof(short));

	init_astar(open, closed, parent, g_cost, 285);

	printf("========MAP========\n");
	for (i = 0; i < 15; i++){
		for (j = 0; j < 19; j++){
			printf("%i", *(map + i*19 + j));
		}
		printf("\n");
	}
	printf("===================\n");
	for (i = 0; i < 5; i++){
		printf("main: %i\n", *(open+i));
	}



	// STEP 1
	
	*(open + start) = 1;
	o_count++;
	*(g_cost + start) = 0;

	current = next_current(open, g_cost, destination, 285);
	printf("%i\n", current);

}

static short next_current(short *open, short *g_cost, short destination, short size){
	short f_cost_min = 9999;
	short f_cost = 0;
	short nextCurrent = 0;

	short nextCurrentX = 0;
	short nextCurrentY = 0;
	short prevCurrentX = 0;
	short prevCurrentY = 0;
	short destinationX = 0;
	short destinationY = 0;

	short prev_manhattan = 0;
	short curr_manhattan = 0;
	short i;


	for (i = 0; i < size; i++){
		if (*(open + i) == 1){
			nextCurrentX = i % 19;
			nextCurrentY = i / 19;
			destinationX = destination % 19;
			destinationY = destination / 19;
			curr_manhattan = manhattan(nextCurrentX, nextCurrentY, destinationX, destinationY);
			f_cost =  *(g_cost + i) + curr_manhattan;
			if (f_cost < f_cost_min){
				f_cost_min = f_cost;
				nextCurrent = i;
			}else if(f_cost == f_cost_min){
				prevCurrentX = i % 19;
				prevCurrentY = i / 19;
				prev_manhattan = manhattan(prevCurrentX, prevCurrentY, destinationX, destinationY);
				if(curr_manhattan <= prev_manhattan){
					f_cost_min = f_cost;
					nextCurrent = i;
				}
			}
		}
	}

	return nextCurrent;
}

void init_astar(short *open, short* closed, short* parent, short* g_cost, short size){
	short i;

	for (i = 0; i < size; i++){
		*(open + i) = -1;
		*(closed + i) = -1;
		*(parent + i) = -1;
		*(g_cost + i) = -1;
	}
}

static uint8 is_empty(short *list, short size){
	short i;

	for (i = 0; i < size; i++){
		if (*(list + i) == 1){
			return 0;
		}
	}
	return 1;
}


static uint8 in_set(short* array, short node){
	short i;

	if (*(array + node) == 1){
		return 1;
	}

	return 0;
}

short manhattan(uint8 x1, uint8 y1, uint8 x2, uint8 y2){
	return abs(x2-x1) + abs(y2-y1);
}

/* [] END OF FILE */
