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

#include "map.h"
#include "dfs_vertex.h"
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

int get_index(int16_t *route, int steps, int node){
	int i;
	for(i = 0; i < steps ; i++){
		if( *(route+i) == node){
			return i;
		}
	}
	return 0;
}

void p_decision(decision_type decision){

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
}
uint16_t conv_to_node(uint16_t x,uint16_t y){
	return y*MAP_WIDTH + x;
}
int main(void){
	int* mapp;
	int16_t* route;
	int i,j;
	uint16_t steps = 0;

	uint16_t start = 0;
	uint16_t* vertex_list;
	uint16_t* vertex_seq;
	start = conv_to_node(1,7);
	route = (int16_t*)malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(int16_t));
	vertex_list = (int16_t*)malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(int16_t));
	vertex_seq = (int16_t*)malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(int16_t));
	steps = dfs_traverse(route,start);
	int vertex_counter;
	vertex_counter =  0;
	int vertex_index = 0;
	for(i = 0; i < steps;i ++){
		if(is_vertex(*(route+i))){
			*(vertex_list+vertex_index) = *(route+i);
			*(vertex_seq+vertex_index) = vertex_index;
			vertex_index++;
		}
	}

	printf("vertex_index: %d\n",vertex_index );
	for (i = 0; i < 15; i++){
		for (j = 0; j < 19; j++){
			if (map[i][j] == 1){
				printf("%c", '#');
			} else {

				if(in_sett(vertex_list,vertex_index,conv_to_node(i,j))){
					printf("%d",*(vertex_seq + get_index(vertex_list,vertex_index,conv_to_node(i,j))));
					vertex_counter++;
				}else{
					printf("%c", ' ');
				}
			}
		}
		printf("\n");
	}
	printf("total vertices count: %d\n",vertex_counter);
	free(vertex_list);
	free(vertex_seq);
	free(route);

	
	
	return 0;
}














/* [] END OF FILE */
