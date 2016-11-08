#include "dfs_vertex.h"



uint8_t is_vertex(const uint16_t node){
	uint16_t x_cell = node % MAP_WIDTH;
	uint16_t y_cell = node / MAP_WIDTH;

	if(map[x_cell][y_cell] == 1){
		return 0;
	} else{
		if(map[x_cell][y_cell-1] == 0 && map[x_cell][y_cell+1] == 0){
			if(map[x_cell+1][y_cell] == 1 && map[x_cell - 1][y_cell] == 1){
				return 0;
			} else if(map[x_cell + 1][y_cell] == 0 || map[x_cell - 1][y_cell] == 0){
				return 1;
			} 
			
		} else if(map[x_cell-1][y_cell] == 0 && map[x_cell+1][y_cell] == 0){
			if(map[x_cell][y_cell + 1] == 1 && map[x_cell][y_cell - 1] ==1){
				return 0;
			} else if(map[x_cell][y_cell + 1] == 0 || map[x_cell][y_cell - 1] == 0){
				return 1;
			}
		} else{
			return 1;
		}
	}

	return 0;

}