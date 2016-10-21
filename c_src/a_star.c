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

#include "a_star.h"
#include "simulation.h"

static int16_t is_open_empty(int16_t *map_status, int16_t size);
static int16_t next_current(int16_t *map_status, int16_t *g_cost, int16_t *addi_cost, int16_t destination, int16_t size);
static int16_t update_surrounding(int16_t *map, int16_t *map_status, int16_t *g_cost, int16_t *parent, int16_t current);
static int16_t trace_back(int16_t *traced_route, int16_t *parent, int16_t destination, int16_t start);
static void flip_trace(int16_t *source, int16_t *target, int16_t size);
static int16_t manhattan(int16_t l1, int16_t l2);

int16_t a_star(int16_t *map, int16_t *addi_cost, int16_t *route, int16_t start, int16_t destination){
	int16_t *map_status, *parent, *g_cost, *traced_route;
	int16_t current;
	int16_t steps = 0;

	if (destination > MAP_WIDTH*MAP_HEIGHT || destination < 0){
		// printf("INVALID DESTINATION\n");
		return -1;
	} else if (start > MAP_WIDTH*MAP_HEIGHT || start < 0){
		// printf("INVALID START\n");
		return -2;
	} else if (*(&map + destination) == 1){
		// printf("INVALID DESTINATION\n");
		return -3;
	} else if (*(map + start) == 1){
		// printf("INVALID START\n");
		return -4;
	}


	map_status = (int16_t*)calloc(MAP_WIDTH*MAP_HEIGHT, sizeof(int16_t));
	parent = (int16_t*)calloc(MAP_WIDTH*MAP_HEIGHT, sizeof(int16_t));
	g_cost = (int16_t*)calloc(MAP_WIDTH*MAP_HEIGHT, sizeof(int16_t));
	traced_route = (int16_t*)calloc(MAP_WIDTH*MAP_HEIGHT, sizeof(int16_t));


	#ifdef SIMULATION_H
		int16_t i, j;
		printf("========MAP========\n\n");

		for (i = 0; i < 15; i++){
			for (j = 0; j < 19; j++){
				printf("%c", *(map + i*19 + j) == 0? ' ':'#');
			}
			printf("\n");
		}

		printf("\n===================\n\n");
	#endif

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

	*(map_status + start) = OPEN;


	while(!is_open_empty(map_status, MAP_HEIGHT*MAP_HEIGHT)){
		current = next_current(map_status, g_cost, addi_cost, destination, MAP_HEIGHT*MAP_HEIGHT);
		printf("current = %i\n", current);
		if (current == destination){
			#ifdef SIMULATION_H
			 	printf("DESTINATION REACHED\n");
			#endif

			//LED_Write(1);
			break;
		}

		update_surrounding(map, map_status, g_cost, parent, current);
	}

	steps = trace_back(traced_route, parent, destination, start);
	flip_trace (traced_route, route, steps);


	#ifdef SIMULATION_H
		printf("STEPS = %i\n", steps);

		for (i = 0; i < steps; i++){
			printf("traced_route[%i] = %i (%i, %i)\n", i, *(traced_route+i), *(traced_route+i)%MAP_WIDTH, *(traced_route+i)/MAP_WIDTH);
		}

		for (i = 0; i < steps; i++){
			printf("route[%i] = %i (%i, %i)\n", i, *(route+i),*(route+i)%MAP_WIDTH, *(route+i)/MAP_WIDTH);
		}
	#endif


	free(map_status);
	free(parent);
	free(g_cost);
	free(traced_route);

	return steps;
}

// Check whether there are any open nodes remaining
static int16_t is_open_empty(int16_t *map_status, int16_t size){
	int16_t i;

	for (i = 0; i < size; i++){
		if (*(map_status + i) == OPEN){
			return 0;
		}
	}

	return 1;
}

static int16_t next_current(int16_t *map_status, int16_t *addi_cost, int16_t *g_cost, int16_t destination, int16_t size){
	int16_t f_cost_min = SHRT_MAX, f_cost;	// SHRT_MAX = 32767
	int16_t h_cost_next;
	int16_t current_next, current_next_best;
	int16_t i;

	for (i = 0; i < size; i++){
		if (*(map_status + i) == OPEN){
			h_cost_next = manhattan(i, destination);
			f_cost = *(g_cost + i) + *(addi_cost + i) + h_cost_next;

			if (f_cost < f_cost_min){
				f_cost_min = f_cost;
				current_next_best = i;
			}
		}
	}

	*(map_status + current_next_best) = CLOSED;

	return current_next_best;
}

// For the current node, update surrounding nodes' status
static int16_t update_surrounding(int16_t *map, int16_t *map_status, int16_t *g_cost, int16_t *parent, int16_t current){
	int16_t i;
	int16_t o_count = 0;
	int16_t temp;

	// North
	temp = current - MAP_WIDTH;

	if (temp >= 0 &&  *(map + temp) == TRACK && *(map_status + temp) != CLOSED){
		*(map_status + temp) = OPEN;
		*(parent + temp) = current;
		*(g_cost + temp) = *(g_cost + current) + 1;
		o_count++;

		// printf("open North added at %i, %i\n", temp%19, temp/19);
	}

	// South
	temp = current + MAP_WIDTH;

	if (temp < MAP_WIDTH * MAP_HEIGHT &&  *(map + temp) == TRACK && *(map_status + temp) != CLOSED){
		*(map_status + temp) = OPEN;
		*(parent + temp) = current;
		*(g_cost + temp) = *(g_cost + current) + 1;
		o_count++;

		// printf("open South added at %i, %i\n", temp%19, temp/19);
	}

	// West
	temp = current - 1;

	if (temp >= 0 &&  *(map + temp) == TRACK && *(map_status + temp) != CLOSED){
		*(map_status + temp) = OPEN;
		*(parent + temp) = current;
		*(g_cost + temp) = *(g_cost + current) + 1;
		o_count++;

		// printf("open West added at %i, %i\n", temp%19, temp/19);
	}

	// East
	temp = current + 1;

	if (temp < MAP_WIDTH * MAP_HEIGHT &&  *(map + temp) == TRACK && *(map_status + temp) != CLOSED){
		*(map_status + temp) = OPEN;
		*(parent + temp) = current;
		*(g_cost + temp) = *(g_cost + current) + 1;
		o_count++;

		// printf("open East added at %i, %i\n", temp%19, temp/19);
	}

	return o_count;


}

// Using parent array, trace back from destination to start
static int16_t trace_back(int16_t *traced_route, int16_t *parent, int16_t destination, int16_t start){
	int16_t steps = 0;
	int16_t current = destination;

	*(traced_route + steps) = current;
	steps++;

	while (current != start){
		*(traced_route + steps) = *(parent + current);
		current = *(parent + current);
		steps++;
	}
	
	return steps;
}

// Flip the traced back array and store content to target
static void flip_trace(int16_t *source, int16_t *target, int16_t size){
	int16_t i;

	for (i = 0; i < size; i++){
		*(target + i) = *(source + size - i - 1);
	}
}



// Calulate the Manhattan distance between two points (H_cost)
static int16_t manhattan(int16_t l1, int16_t l2){
	int16_t x1 = l1%MAP_WIDTH;
	int16_t y1 = l1/MAP_WIDTH;

	int16_t x2 = l2%MAP_WIDTH;
	int16_t y2 = l2/MAP_WIDTH;

	return abs(x2-x1) + abs(y2-y1);
}

