#ifndef _DEFINES_
#define _DEFINES_
#include <stdio.h>
#include <stdlib.h>


typedef enum {TURN_LEFT, TURN_RIGHT, TURN_AROUND, STRAIGHT, STOP, UNKNOWN} decision_type;
typedef enum {TURNING, GOING_STRAIGHT, ADJUSTING, STOPPED} motion_type;


#endif