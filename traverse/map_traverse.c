#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "map.h"

// other functions
int printMap(int posX, int posY);
void clrscr();
void waitFor (clock_t delay);
int rng(int max);

void rule_00(); // random rule
void rule_01(); // other predefined rules
void rule_02();
void rule_03();
void rule_04();


// globals
typedef enum {NORTH, SOUTH, EAST, WEST} dir_enum;
dir_enum direction = NORTH;
int* ruleUse[4] = {0,0,0,0};
// initialize position
int posX = 17;
int posY = 13;

//dfs declarations
void recurse_dfs(int* path);
int convDigi(int x, int y);
void rule_dfs(int* path,int *i);
void generate_path(int* path);
void addPath(int *path);
int food_count();
int path_size = 300;
int t_map[15][19];
int path_i = 0;
int dX, dY;



int main() {
	// y = 0 ~ 14  x = 0 ~ 18 dimensions
	int rule = 0;
	int wait = 0;
	// mode select
	clrscr();
	printf("\n Travel rule (0 ~ 5): ");
	scanf("%d", &rule);
	clrscr();
	printf("\n Wait mode? (1 = Yes): ");
	scanf("%d", &wait);

	int i = 0;
	int timeLimit = 10 * 60;
	int food;

	int *path;

	// initial print
	food = printMap(posX, posY);

	if (rule == 5){
		path = (int*)malloc(path_size * sizeof(int));
		memcpy(t_map,map,sizeof(int)*15*19);
		generate_path(path);
		memset(t_map,0,sizeof(int)*15*19);
	}
	waitFor(3);

	// process rule
	while (i < timeLimit){
		food = printMap(posX, posY);
		printf("PosX: %d PosY: %d\n", posX, posY);
		if (food == 0){
			break;
		}
		map[posY][posX] = 2;

		if (rule == 0){ // random
			rule_00();
		}else if (rule == 1){ // turn clockwise priority
			rule_01();
		}else if (rule == 2){ // force turn clockwise
			rule_02();
		}else if (rule == 3){
			rule_03();
		}else if (rule == 4){
			rule_04();
		}else if (rule == 5){
			rule_dfs(path, &i);
			if (i >= path_i){
				break;
			}
			printf("Progress: %d/%d\n", i, path_i);
		}else {
			break;
		}

		if (wait == 1){
			waitFor(1);
		}
		i++;
	}
	// random rule statistics
	if (rule == 0){
		int j;
		for (j = 0; j < 4; j++){
			printf("Rule 0%d: %d\n", j + 1, ruleUse[j]);
		}
	}else if (rule == 5){
		printf("DFS Iterations: %d\n", i);
	}
	// end statistics
	printf("Time elapsed: %0.2f min\n", ((float)i/60.0));
	printf("Food remaining: %d\n", food);

    return 0;
}

// redraw map
int printMap(int posX, int posY){
	int cnt = 0; // number of food

	clrscr();
	printf ("=========+ MAP +=========\n\n   ");
	int i, j;
	for (i = 0; i < 15; i++){ // y
		for (j = 0; j < 19; j++){ // x
			if (posX == j && posY == i){ // robot
				printf("%c", (map[i][j] != 1)?'o':'X');
			}else{
				if (map[i][j] == 1){ // wall
					printf("%c",'#');
				} else if (map[i][j] == 0){
					printf("%c",'-'); // food
					cnt++;
				} else {
					printf("%c",' '); // cleared
				}
			}
		}
		printf("\n   ");
	}
	printf ("\n=========================\n");
	
	return cnt;
}


// screen clear for map
void clrscr(){
    system("@cls||clear");
}

// delay function
void waitFor (clock_t delay) {
	clock_t t = clock() + (delay * CLOCKS_PER_SEC);
	while (clock() < t);
}

// RNG between 1 and max
int rng(int max) {
    srand((unsigned)time(NULL));
    return (rand() % max) + 1;
}


// random between the rules
void rule_00 (){
	int r;
	r = rng(4);
	if (r == 1){
		rule_01();
	}else if (r == 2){
		rule_02();
	}else if (r == 3){
		rule_03();
	}else if (r == 4){
		rule_04();
	}
	ruleUse[r - 1] += 1;
}

// T intersection turn clockwise
// X intersection go straight
void rule_01 (){
	if (direction == NORTH){ // 1
		if (map[posY - 1][posX] != 1){
			posY--;
		}else if (map[posY][posX + 1] != 1){
			posX++;
			direction = EAST;
		}else if (map[posY][posX - 1] != 1){
			posX--;
			direction = WEST;
		}else{
			posY++;
			direction = SOUTH;
		}	
	}else if (direction == SOUTH){ // 2
		if (map[posY + 1][posX] != 1){
			posY++;
		}else if (map[posY][posX - 1] != 1){
			posX--;
			direction = WEST;
		}else if (map[posY][posX + 1] != 1){
			posX++;
			direction = EAST;
		}else{
			posY--;
			direction = NORTH;
		}	
	}else if (direction == EAST){ // 3
		if (map[posY][posX + 1] != 1){
			posX++;
		}else if (map[posY + 1][posX] != 1){
			posY++;
			direction = SOUTH;
		}else if (map[posY - 1][posX] != 1){
			posY--;
			direction = NORTH;
		}else{
			posX--;
			direction = WEST;
		}	
	}else if (direction == WEST){  // 4
		if (map[posY][posX - 1] != 1){
			posX--;
		}else if (map[posY - 1][posX] != 1){
			posY--;
			direction = NORTH;
		}else if (map[posY + 1][posX] != 1){
			posY++;
			direction = SOUTH;
		}else{
			posX++;
			direction = EAST;
		}	
	}
}

// T and X intersection turn clockwise
void rule_02 (){
	if (direction == NORTH){ // 1
		if (map[posY][posX + 1] != 1){
			posX++;
			direction = EAST;
		}else if (map[posY - 1][posX] != 1){
			posY--;
		}else if (map[posY][posX - 1] != 1){
			posX--;
			direction = WEST;
		}else{
			posY++;
			direction = SOUTH;
		}	
	}else if (direction == SOUTH){ // 2
		if (map[posY][posX - 1] != 1){
			posX--;
			direction = WEST;
		}else if (map[posY + 1][posX] != 1){
			posY++;
		}else if (map[posY][posX + 1] != 1){
			posX++;
			direction = EAST;
		}else{
			posY--;
			direction = NORTH;
		}	
	}else if (direction == EAST){ // 3
		if (map[posY + 1][posX] != 1){
			posY++;
			direction = SOUTH;
		}else if (map[posY][posX + 1] != 1){
			posX++;
		}else if (map[posY - 1][posX] != 1){
			posY--;
			direction = NORTH;
		}else{
			posX--;
			direction = WEST;
		}	
	}else if (direction == WEST){  // 4
		if (map[posY - 1][posX] != 1){
			posY--;
			direction = NORTH;
		}else if (map[posY][posX - 1] != 1){
			posX--;
		}else if (map[posY + 1][posX] != 1){
			posY++;
			direction = SOUTH;
		}else{
			posX++;
			direction = EAST;
		}	
	}
}

// T intersection turn anti-clockwise
// X intersection go straight
void rule_03 (){
	if (direction == NORTH){ // 1
		if (map[posY - 1][posX] != 1){
			posY--;
		}else if (map[posY][posX - 1] != 1){
			posX--;
			direction = WEST;
		}else if (map[posY][posX + 1] != 1){
			posX++;
			direction = EAST;
		}else{
			posY++;
			direction = SOUTH;
		}	
	}else if (direction == SOUTH){ // 2
		if (map[posY + 1][posX] != 1){
			posY++;
		}else if (map[posY][posX + 1] != 1){
			posX++;
			direction = EAST;
		}else if (map[posY][posX - 1] != 1){
			posX--;
			direction = WEST;		
		}else{
			posY--;
			direction = NORTH;
		}	
	}else if (direction == EAST){ // 3
		if (map[posY][posX + 1] != 1){
			posX++;
		}else if (map[posY - 1][posX] != 1){
			posY--;
			direction = NORTH;
		}else if (map[posY + 1][posX] != 1){
			posY++;
			direction = SOUTH;
		}else{
			posX--;
			direction = WEST;
		}	
	}else if (direction == WEST){  // 4
		if (map[posY][posX - 1] != 1){
			posX--;
		}else if (map[posY + 1][posX] != 1){
			posY++;
			direction = SOUTH;
		}else if (map[posY - 1][posX] != 1){
			posY--;
			direction = NORTH;
		}else{
			posX++;
			direction = EAST;
		}	
	}
}

// T and X intersection turn anti clockwise
void rule_04 (){
	if (direction == NORTH){ // 1
		if (map[posY][posX - 1] != 1){
			posX--;
			direction = WEST;
		}else if (map[posY - 1][posX] != 1){
			posY--;
		}else if (map[posY][posX + 1] != 1){
			posX++;
			direction = EAST;
		}else{
			posY++;
			direction = SOUTH;
		}	
	}else if (direction == SOUTH){ // 2
		if (map[posY][posX + 1] != 1){
			posX++;
			direction = EAST;
		}else if (map[posY + 1][posX] != 1){
			posY++;
		}else if (map[posY][posX - 1] != 1){
			posX--;
			direction = WEST;
		}else{
			posY--;
			direction = NORTH;
		}	
	}else if (direction == EAST){ // 3
		if (map[posY - 1][posX] != 1){
			posY--;
			direction = NORTH;
		}else if (map[posY][posX + 1] != 1){
			posX++;
		}else if (map[posY + 1][posX] != 1){
			posY++;
			direction = SOUTH;
		}else{
			posX--;
			direction = WEST;
		}	
	}else if (direction == WEST){  // 4
		if (map[posY + 1][posX] != 1){
			posY++;
			direction = SOUTH;		
		}else if (map[posY][posX - 1] != 1){
			posX--;
		}else if (map[posY - 1][posX] != 1){
			posY--;
			direction = NORTH;
		}else{
			posX++;
			direction = EAST;
		}	
	}
}

void generate_path(int* path){
	dX = posX;
	dY = posY;
	recurse_dfs(path);
	printf("%d >> food:%d\n", path_i, food_count());
}

void addPath(int *path){
	if (food_count() == 0){
		return;
	}
	printf("%d >> dXdY:(%d,%d) food:%d\n", path_i, dX, dY, food_count());
	path[path_i] = convDigi(dX,dY); // add to list
	t_map[dY][dX] = 2; // set to seen
	path_i++;
	if (path_i >= path_size){ // overflow check
		path_size += 300;
		path = (int*)realloc(path, path_size);
	}	
}

void recurse_dfs(int* path){
	int tX = dX;
	int tY = dY;

	addPath(path);	

	
	if (t_map[dY - 1][dX] == 0){ // north
		dY -= 1;
		recurse_dfs(path);
		dX = tX;
		dY = tY;
		addPath(path);	
	}
	if (t_map[dY + 1][dX] == 0){ // south
		dY += 1;
		recurse_dfs(path);
		dX = tX;
		dY = tY;
		addPath(path);	
	}
	if (t_map[dY][dX - 1] == 0){ // west
		dX -= 1;
		recurse_dfs(path);
		dX = tX;
		dY = tY;
		addPath(path);	
	}
	if (t_map[dY][dX + 1] == 0){ // east
		dX += 1;
		recurse_dfs(path);
		dX = tX;
		dY = tY;
		addPath(path);	
	}
}

int food_count(){
	int cnt = 0, i, j;
	for (i = 0; i < 15; i++){ // y
		for (j = 0; j < 19; j++){ // x
			if (t_map[i][j] == 0){
				cnt++;
			}
		}
	}
	return cnt;
}

void rule_dfs(int* path,int *i){
	posX = path[*(i)] % 19;
	posY = path[*(i)] / 19;
}

int convDigi(int x, int y){
	return y * 19 + x;
}