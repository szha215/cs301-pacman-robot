#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "map.h"
#include <time.h>


#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4


void printMap(int posX, int posY);
void clrscr();
void waitFor (unsigned int secs);


int main()
{
	// y = 0 ~ 14
	// x = 0 ~ 18
	int posX = 1;
	int posY = 1;
	int direction = NORTH;
	printMap(posX, posY);

	while (1){
		printMap(posX, posY);
		
		if (direction == NORTH){ // 1
			if (map[posY - 1][posX] == 0){
				posY--;
			}else if (map[posY][posX + 1] == 0){
				posX++;
				direction = EAST;
			}else if (map[posY][posX - 1] == 0){
				posX--;
				direction = WEST;
			}else{
				posY++;
				direction = SOUTH;
			}	
		}else if (direction == SOUTH){ // 2
			if (map[posY + 1][posX] == 0){
				posY++;
			}else if (map[posY][posX - 1] == 0){
				posX--;
				direction = WEST;
			}else if (map[posY][posX + 1] == 0){
				posX++;
				direction = EAST;
			}else{
				posY--;
				direction = NORTH;
			}	
		}else if (direction == EAST){ // 3
			if (map[posY][posX + 1] == 0){
				posX++;
			}else if (map[posY + 1][posX] == 0){
				posY++;
				direction = SOUTH;
			}else if (map[posY][posX - 1] == 0){
				posY--;
				direction = NORTH;
			}else{
				posX--;
				direction = WEST;
			}	
		}else if (direction == WEST){  // 4
			if (map[posY][posX - 1] == 0){
				posX--;
			}else if (map[posY - 1][posX] == 0){
				posY--;
				direction = NORTH;
			}else if (map[posY + 1][posX] == 0){
				posY++;
				direction = SOUTH;
			}else{
				posX++;
				direction = EAST;
			}	
		}
		waitFor(1);
	}
    return 0;
}

void printMap(int posX, int posY){
	clrscr();
	int i, j;
	for (i = 0; i < 15; i++){ // y
		for (j = 0; j < 19; j++){ // x
			if (posX == j && posY == i){
				printf("%c", (map[i][j] == 0)?'o':'X');
			}else{
				printf("%c", (map[i][j] == 1)?'#':' ');
			}
		}
		printf("\n");
	}
}

void clrscr()
{
    system("@cls||clear");
}




void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}