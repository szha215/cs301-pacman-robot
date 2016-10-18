#ifndef _DEFINES_
#define _DEFINES_
#include <stdio.h>
#include <stdlib.h>


typedef enum {TURN_LEFT, TURN_RIGHT, TURN_AROUND, STRAIGHT, STOP, OUT_OF_BOUNDS} decision_type;
typedef enum {TURNING, TURNING_BUFFER, AT_INTERSECTION, GOING_STRAIGHT, ADJUSTING, STOPPED} motion_type;
typedef enum {STATE_UPDATED,STATE_IN_PROGRESS} update_states;

#endif