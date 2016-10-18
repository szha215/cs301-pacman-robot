#include "dfs_traverse.h"

int16_t dfs_traverse(int16_t *path, int16_t start){
	dX = start % 19;
	dY = start / 19;
	t_map = (int16_t*)malloc(sizeof(int16_t) * MAP_HEIGHT * MAP_WIDTH);
	memcpy(t_map, map, sizeof(int16_t) * MAP_HEIGHT * MAP_WIDTH);
	path_i = 0;
	recurse_dfs(path);
	printf("%d >> food:%d\n", path_i, food_count());
	free(t_map);
	return (int16_t)path_i;
}


void addPath(int16_t *path){
	if (food_count() == 0){return;}
	printf("%d >> food at %d (%d,%d) food:%d\n", path_i, dY*19+dX, dX, dY, food_count());
	path[path_i] = convDigi(dY,dX); // add to list
	t_map[convDigi(dY,dX)] = 2; // set to seen
	path_i++;
}

void recurse_dfs(int16_t* path){
	int16_t tX = dX;
	int16_t tY = dY;

	addPath(path);	

	if (dY != 0){ // out bounds check
		if (t_map[convDigi(dY - 1,dX)] == 0){ // north
			dY -= 1;
			recurse_dfs(path);
			dX = tX;
			dY = tY;
			addPath(path);	
		}
	}
	if (dY != (MAP_HEIGHT - 1)){
		if (t_map[convDigi(dY + 1,dX)] == 0){ // south
			dY += 1;
			recurse_dfs(path);
			dX = tX;
			dY = tY;
			addPath(path);	
		}
	}
	if (dX != 0){
		if (t_map[convDigi(dY,dX - 1)] == 0){ // west
			dX -= 1;
			recurse_dfs(path);
			dX = tX;
			dY = tY;
			addPath(path);	
		}
	}
	if (dX != (MAP_WIDTH - 1)){
		if (t_map[convDigi(dY,dX + 1)] == 0){ // east
			dX += 1;
			recurse_dfs(path);
			dX = tX;
			dY = tY;
			addPath(path);	
		}
	}
}

int16_t food_count(){
	int16_t cnt = 0, i, j;
	for (i = 0; i < 15; i++){ // y
		for (j = 0; j < 19; j++){ // x
			if (t_map[convDigi(i,j)] == 0){
				cnt++;
			}
		}
	}
	return cnt;
}

int16_t convDigi(int16_t y, int16_t x){
	return y * 19 + x;
}