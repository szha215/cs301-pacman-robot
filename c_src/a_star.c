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


static int16_t manhattan(int16_t l1, int16_t l2);

int16_t a_star(int16_t *route, int16_t start, int16_t destination){
	int16_t *map_status, *parent, *g_cost, *traced_route;
	int16_t current;
	int16_t i, steps = 0;


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


	return steps;
}

// Check whether there are any open nodes remaining
static int16_t open_empty(int16_t *map_status, int16_t size){
	int16_t i;

	for (i = 0; i < size; i++){
		if (*(map_status + i) == OPEN){
			return 0;
		}
	}

	return 1;
}

// For the current node, update surrounding nodes' status
static int16_t update_surrounding(int16_t *map_status, int16_t *g_cost, int16_t *parent, int16_t current){

}

// Using parent array, trace back from destination to start
static int16_t trace_back(int16_t *traced_route, int16_t *parent, int16_t destination, int16_t start){
	int16_t steps = 0;
	int16_t current = destination;

	*(traceback + steps) = current;
	steps++;

	while (current != start){
		*(traceback + steps) = *(parent + current);
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

