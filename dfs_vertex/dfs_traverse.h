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


#ifndef DFS_TRAVERSE_H
#define DFS_TRAVERSE_H

#include "map.h"
#include <stdint.h>

#define MAP_WIDTH 19
#define MAP_HEIGHT 15

int16_t dfs_traverse(int16_t *path, int16_t start);
void recurse_dfs(int16_t* path);
void addPath(int16_t *path);
int16_t food_count();
int16_t convDigi(int16_t y, int16_t x);
int16_t* t_map;
int16_t path_i;
int16_t dX, dY;






#endif