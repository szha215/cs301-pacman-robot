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

#ifndef RF_HANDLER_H
#define RF_HANDLER_H


#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RXSTRINGSIZE 32
#define SOP 0xaa
#define TOGGLE_LED LED_Write(~LED_Read())
#define ADJUST_RIGHT 1
#define ADJUST_LEFT 2
#define NOT_ADJUSTING 0
#define Y_THRESHOLD 50 //in px
#define ANGLE_THRESHOLD 50
static volatile uint8 indexCount = 0;
static volatile uint8 endCount = 0;
char rxString[RXSTRINGSIZE];
static volatile  int rx_recieved = 0;
static volatile uint8 rx_handled = 0;

// struct define with all the data
typedef struct data_main {
	int8           rssi;				// recieve signal strength index
    uint8          index;				// index number of packet. incremented number
	uint16         robot_xpos;	 		// x pos of robot
	uint16         robot_ypos;			// y pos of robot
    uint16         robot_orientation;	// angle of robot
	uint16         g0_xpos;				// x pos of ghost 0
	uint16         g0_ypos;				// y pos of ghost 0
	uint16         g0_speed;			// move speed of ghost 0
	uint16         g0_direction;		// angle of ghost 0
	uint16         g1_xpos;				// x pos of ghost 1
	uint16         g1_ypos;				// y pos of ghost 1
	uint16         g1_speed;			// move speed of ghost 1
    uint16         g1_direction;		// angle of ghost 1
    uint16         g2_xpos;				// x pos of ghost 2
    uint16         g2_ypos;				// y pos of ghost 2
    uint16         g2_speed;			// move speed of ghost 2
    uint16         g2_direction;		// angle of ghost 2
} data_main;



// process rf string into struct
// in_string = string to decode
// out_struct = struct to allocate decoded values
void handle_rx(char* in_string, data_main *out_struct);
data_main* rf_Handler_init();
void check_RF(data_main* RF_data);

uint8 is_handled();
void clear_handled();

#endif
/* [] END OF FILE */
