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
#include "map.h"




int16_t map[15][19] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
{1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
{1,0,1,0,1,0,0,0,1,1,1,0,1,0,1,1,1,0,1},
{1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1},
{1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1},
{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
{1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1},
{1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1},
{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
{1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int food_packets[5][2] = {
	{1,3},
	{3,7},
	{16,3},
	{9,7},
	{17,13}
};
// int food_packets[5][2] = {
// 	{1,3},
// 	{3,7},
// 	{9,7},
// 	{16,3},
// 	{17,13}
// };
/* [] END OF FILE */
