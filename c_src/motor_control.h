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

#include "project.h"

#define STOP 128
#define M_FORWARD_MAX 255
#define M_BACKWARD_MAX 0

#define M1_FORWARD 160
#define M2_FORWARD 165

#define M1_FORWARD_SLOW 156
#define M2_FORWARD_SLOW 160

#define M1_BACKWARD 91
#define M2_BACKWARD 88

extern uint8 compare_val_m1;
extern uint8 compare_val_m2;


void init_motor_control();

// stop both
void m_stop();

// both wheels straight
void m_straight();
void m_straight_slow();

// one wheel slow forward, one wheel forward
void m_adjust_left();
void m_adjust_right();

// one wheel backward, one wheel forward
void m_turn_left();
void m_turn_right();






/* [] END OF FILE */
