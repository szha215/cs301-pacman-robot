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




int mapp[15][19] = {
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

int food_packetss[5][2] = {
	{1, 3},
	{3,7},
	{16,3},
	{9,7},
	{15,13}
};
	 
/* [] END OF FILE */
