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
//#include "project.h"
// #include "project.h"


static void init_astar(int16_t *open, int16_t *closed, int16_t *parent, int16_t *g_cost, int16_t size);
static uint8_t is_empty(int16_t *list, int16_t size);
static int16_t next_current(int16_t *open, int16_t *g_cost, int16_t *addi_cost, int16_t destination, int16_t size);
static void add_closed(int16_t *closed, int16_t location);
static uint8_t add_open(int16_t *map, int16_t *open, int16_t *closed, int16_t *g_cost, int16_t *parent, int16_t current);
static uint8_t traceback(int16_t *parent, int16_t *traceback, int16_t destination, int16_t start);
static void flip_array(int16_t *source, int16_t *target, int16_t size);
static int16_t manhattan(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

 
int16_t astar(int16_t map[15][19], int16_t *addi_cost, int16_t *route, int16_t start, int16_t destination){
	int16_t *open, *closed, *parent, *g_cost, *traced_route;
	int16_t current;
	uint16_t i, steps;

	// printf("size of map = %i\n\n", sizeof(int16_t));

	if (destination > MAP_WIDTH*MAP_HEIGHT || destination < 0){
		// printf("INVALID DESTINATION\n");
		return -1;
	} else if (start > MAP_WIDTH*MAP_HEIGHT || start < 0){
		// printf("INVALID START\n");
		return -2;
	} else if (*(map + destination) == 1){
		// printf("INVALID DESTINATION\n");
		return -3;
	} else if (*(map + start) == 1){
		// printf("INVALID START\n");
		return -4;
	}


	open = (int16_t*)malloc(285 * sizeof(int16_t));
	closed = (int16_t*)malloc(285 * sizeof(int16_t));
	parent = (int16_t*)malloc(285 * sizeof(int16_t));
	g_cost = (int16_t*)malloc(285 * sizeof(int16_t));
	traced_route = (int16_t*)malloc(285 * sizeof(int16_t));


	init_astar(open, closed, parent, g_cost, 285);

	// printf("========MAP========\n\n");
	// for (i = 0; i < 15; i++){
		// for (j = 0; j < 19; j++){
			// printf("%c", *(map + i*19 + j) == 0? ' ':'#');
		// }
		// printf("\n");
	// }
	// printf("\n===================\n\n");


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
	*(g_cost + start) = 0;

	while (!is_empty(open, 285)){
		current = next_current(open, g_cost, addi_cost, destination, 285);
		// printf("current = %i, %i\n", current%19, current/19);
		add_closed(closed, current);
		add_open(map, open, closed, g_cost, parent, current);


		if (current == destination){
			// printf("DESTINATION REACHED\n");
			break;
		}
		
	}

	steps = traceback(parent, traced_route, destination, start);


	// printf("STEPS = %i\n", steps);
	
	for (i = 0; i < steps; i++){
		// printf("traced_route[%i] = %i (%i, %i)\n", i, *(traced_route+i), *(traced_route+i)%MAP_WIDTH, *(traced_route+i)/MAP_WIDTH);
	}
	
	flip_array(traced_route, route, steps);

	for (i = 0; i < steps; i++){
		printf("route[%i] = %i (%i, %i)\n", i, *(route+i),*(route+i)%MAP_WIDTH, *(route+i)/MAP_WIDTH);
	}

	// printf("closed [start] = %i\n", *(closed+start));

	// printf("%i\n", add_open(map, open, closed, parent, current));


	free(parent);
	
	free(open);
	free(closed);
	free(g_cost);
	free(traced_route);

	//memcpy(route, closed, (MAP_WIDTH*MAP_HEIGHT-1) * sizeof(int16_t));

	return steps;
}

static int16_t next_current(int16_t *open, int16_t *g_cost, int16_t *addi_cost, int16_t destination, int16_t size){
	int16_t f_cost_min = SHRT_MAX;	// 32767
	int16_t f_cost = 0;
	int16_t bestCurrent = 0;

	int16_t nextCurrentX = 0;
	int16_t nextCurrentY = 0;
	int16_t bestCurrentX = 0;
	int16_t bestCurrentY = 0;
	int16_t destinationX = destination % 19;
	int16_t destinationY = destination / 19;

	int16_t best_manhattan = 0;
	int16_t next_manhattan = 0;
	int16_t i;

	// printf("int16_t MAX = %i\n", f_cost_min);

	for (i = 0; i < size; i++){
		if (*(open + i) == 1){
			nextCurrentX = i % 19;
			nextCurrentY = i / 19;
			bestCurrentX = bestCurrent % 19;
			bestCurrentY = bestCurrent / 19;
			next_manhattan = manhattan(nextCurrentX, nextCurrentY, destinationX, destinationY);
			f_cost =  *(g_cost + i) + *(addi_cost + i) + next_manhattan;
			if (f_cost < f_cost_min){
				f_cost_min = f_cost;
				bestCurrent = i;
			} else if (f_cost == f_cost_min){
				best_manhattan = manhattan(bestCurrentX, bestCurrentY, destinationX, destinationY);
				if (next_manhattan <= best_manhattan){
					f_cost_min = f_cost;
					bestCurrent = i;
				}
			}
		}
	}

	*(open + bestCurrent) = 0;

	return bestCurrent;
}

static void init_astar(int16_t *open, int16_t* closed, int16_t* parent, int16_t* g_cost, int16_t size){
	int16_t i;

	for (i = 0; i < size; i++){
		*(open + i) = -1;
		*(closed + i) = -1;
		*(parent + i) = -1;
		*(g_cost + i) = -1;
	}
}

static uint8_t is_empty(int16_t *list, int16_t size){
	int16_t i;

	for (i = 0; i < size; i++){
		if (*(list + i) == 1){
			return 0;
		}
	}

	return 1;
}


static void add_closed(int16_t *closed, int16_t location){
	*(closed + location) = 1;
}

static uint8_t add_open(int16_t *map, int16_t *open, int16_t *closed, int16_t *g_cost, int16_t *parent, int16_t current){
	int16_t o_count = 0, temp = 0;

	// North
	temp = current - MAP_WIDTH;

	if (temp >= 0 &&  *(map + temp) == 0 && *(closed + temp) == -1){
		*(open + temp) = 1;
		*(parent + temp) = current;
		*(g_cost + temp) = *(g_cost + current) + 1;
		o_count++;

		// printf("open North added at %i, %i\n", temp%19, temp/19);
	}

	// South
	temp = current + MAP_WIDTH;

	if (temp < MAP_WIDTH * MAP_HEIGHT &&  *(map + temp) == 0 && *(closed + temp) == -1){
		*(open + temp) = 1;
		*(parent + temp) = current;
		*(g_cost + temp) = *(g_cost + current) + 1;
		o_count++;

		// printf("open South added at %i, %i\n", temp%19, temp/19);
	}

	// West
	temp = current - 1;

	if (temp >= 0 &&  *(map + temp) == 0 && *(closed + temp) == -1){
		*(open + temp) = 1;
		*(parent + temp) = current;
		*(g_cost + temp) = *(g_cost + current) + 1;
		o_count++;

		// printf("open West added at %i, %i\n", temp%19, temp/19);
	}

	// East
	temp = current + 1;

	if (temp < MAP_WIDTH * MAP_HEIGHT &&  *(map + temp) == 0 && *(closed + temp) == -1){
		*(open + temp) = 1;
		*(parent + temp) = current;
		*(g_cost + temp) = *(g_cost + current) + 1;
		o_count++;

		// printf("open East added at %i, %i\n", temp%19, temp/19);
	}

	return o_count;
}

static uint8_t traceback(int16_t *parent, int16_t *traceback, int16_t destination, int16_t start){
	uint8_t steps = 0;
	int16_t current = destination;

	*(traceback + steps) = current;
	steps++;

	while (current != start){
		*(traceback + steps) = *(parent + current);
		current = *(parent + current);
		steps++;
	}
	// LED_Write(1);
	return steps;
}

static void flip_array(int16_t *source, int16_t *target, int16_t size){
	uint16_t i;

	for (i = 0; i < size; i++){
		*(target + i) = *(source + size - i - 1);
	}
	// LED_Write(1);
}

static int16_t manhattan(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	return abs(x2-x1) + abs(y2-y1);
}

/* [] END OF FILE */
