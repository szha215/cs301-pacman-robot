#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "map.h"
#include <time.h>
//#include <sys/time.h>

#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4


int printMap(int posX, int posY);
void clrscr();
void waitFor (unsigned int secs);
<<<<<<< HEAD
void protocol_01();
void protocol_02();

int posX = 1;
int posY = 1;
int direction = NORTH;
=======
int map_visited[15][19];
>>>>>>> cb69989e7b8fafc9c7f9ddb6ae9f10312d8d2010

int main()
{
	// y = 0 ~ 14
	// x = 0 ~ 18
<<<<<<< HEAD
	int prot = 1;
	int wait = 0;
	clrscr();
	printf("Protocol (only have 2 protocol, '1 or 2'): ");
	scanf("%d", &prot);
	printf("Wait? (1 = Yes): ");
	scanf("%d", &wait);
=======
	int posX = 1;
	int posY = 1;
	int direction = NORTH;
	int i, j;
	

	memcpy(map_visited, map, sizeof(int) * 15 * 19);
	for (i = 0; i < 14; i++){
		for (j = 0; j < 19; j++){
			if (map_visited[i][j] == 0){
				map_visited[i][j] = 2;	// not visited
			}
		}
	}


>>>>>>> cb69989e7b8fafc9c7f9ddb6ae9f10312d8d2010

	printMap(posX, posY);

	int i = 0;
	int timeLimit = 10 * 60;
	int food = 1;
	while (i < timeLimit){
		food = printMap(posX, posY);
		if (food == 0){
			break;
		}
		map[posY][posX] = 2;
		if (prot == 1){
			protocol_01();
		}else if (prot == 2){
			protocol_02();
		}
<<<<<<< HEAD
		if (wait == 1){
			waitFor(1);
		}
		i++;
=======
		//waitFor(1);
>>>>>>> cb69989e7b8fafc9c7f9ddb6ae9f10312d8d2010
	}
	printf("Time elapsed: %d min\n", (i/60));
	printf("Number of food remaining: %d\n", food);
    return 0;
}





int printMap(int posX, int posY){
	int cnt = 0; // number of food

	clrscr();
	printf ("=========+ MAP +=========\n\n   ");
	int i, j;
	for (i = 0; i < 15; i++){ // y
		for (j = 0; j < 19; j++){ // x
			if (posX == j && posY == i){
<<<<<<< HEAD
				printf("%c", (map[i][j] != 1)?'o':'X');
			}else{
				if (map[i][j] == 1){
					printf("%c",'#');
				} else if (map[i][j] == 0){
					printf("%c",'-');
					cnt++;
				} else {
					printf("%c",' ');
				}
=======
				printf("%c", 'o');
				map_visited[i][j] = 3;
			} else {
				if (map_visited[i][j] == 1){
					printf("%c", '#');
				} else if (map_visited[i][j] == 2) {
					printf("%c", 'x');
				} else {
					printf("%c", ' ');
				}
				
>>>>>>> cb69989e7b8fafc9c7f9ddb6ae9f10312d8d2010
			}
		}
		printf("\n   ");
	}
	printf ("\n=========================\n");
	
	return cnt;
}


void clrscr()
{
    system("@cls||clear");
}


void waitFor (clock_t delay) {
	clock_t t = clock() + (delay * CLOCKS_PER_SEC);
	while (clock() < t);
}


void protocol_01 (){
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

void protocol_02 (){
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