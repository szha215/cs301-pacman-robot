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

short astar(int *map, short width, short height, short *route, short start, short destination){
	short *open, *closed, *parent, *g_cost;
	short o_count, c_count, p_count;
	short current;
	int i, j;

	printf("size of map = %i\n\n", sizeof(short));

	open = (short*)malloc(285 * sizeof(short));
	closed = (short*)malloc(285 * sizeof(short));
	parent = (short*)malloc(285 * sizeof(short));
	g_cost = (short*)malloc(285 * sizeof(short));

	init_astar(open, closed, parent, g_cost, 285);

	printf("========MAP========\n\n");
	for (i = 0; i < 15; i++){
		for (j = 0; j < 19; j++){
			printf("%c", *(map + i*19 + j) == 0? ' ':'#');
		}
		printf("\n");
	}
	printf("\n===================\n\n");


	/* Each iteration should contain:
	1. Find neighbours of current, store in open
	2. For each open node, calculate F cost
	3. Store current node location into open node for parent
	4. Change current node to node with lowest F cost
	5. Remove new current node from open
	6. Add new current node to closed - same as open????

	7. Repeat until current = destination
	8. Trace back using parent until start
	9. Flip traceback array (route)
	10. Store route with memcpy
	*/

	*(open + start) = 1;
	o_count++;
	*(g_cost + start) = 0;

	while (!is_empty(open, 285)){



		break;
	}

	current = next_current(open, g_cost, destination, 285);
	printf("initial current = %i\n", current);
	add_closed(closed, current);
	printf("closed [start] = %i\n", *(closed+start));



	free(parent);
	free(open);
	free(closed);
	free(g_cost);
}

static short next_current(short *open, short *g_cost, short destination, short size){
	short f_cost_min = SHRT_MAX;	// 32767
	short f_cost = 0;
	short nextCurrent = 0;

	short nextCurrentX = 0;
	short nextCurrentY = 0;
	short prevCurrentX = 0;
	short prevCurrentY = 0;
	short destinationX = destination % 19;
	short destinationY = destination / 19;

	short prev_manhattan = 0;
	short curr_manhattan = 0;
	short i;

	printf("short MAX = %i\n", f_cost_min);

	for (i = 0; i < size; i++){
		if (*(open + i) == 1){
			nextCurrentX = i % 19;
			nextCurrentY = i / 19;
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

	*(open + nextCurrent) = 0;

	return nextCurrent;
}

static void init_astar(short *open, short* closed, short* parent, short* g_cost, short size){
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
	return (*(array + node) == 1)? 1:0;
}

static void add_closed(short *closed, short location){
	*(closed + location) = 1;
}

static short manhattan(uint8 x1, uint8 y1, uint8 x2, uint8 y2){
	return abs(x2-x1) + abs(y2-y1);
}

/* [] END OF FILE */
