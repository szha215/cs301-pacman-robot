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

#include <motor_control.h>


void init_motor_control(){
    M1_SLW_Write(1);
    M2_SLW_Write(1);
    
    M1_INV_Write(0);
    M2_INV_Write(0);
    
    M1_ENB_Write(1);
    M2_ENB_Write(1);
    
    M1_D2_Write(1);
    M2_D2_Write(1);

    PWM_M1_Start();
    PWM_M2_Start();
    
}

void m_stop(){
    PWM_M1_WriteCompare(STOP);
    PWM_M2_WriteCompare(STOP);
}

void m_straight(){
    PWM_M1_WriteCompare(M1_FORWARD);
    PWM_M2_WriteCompare(M2_FORWARD);
}

void m_straight_slow(){
    PWM_M1_WriteCompare(M1_FORWARD_SLOW);
    PWM_M2_WriteCompare(M2_FORWARD_SLOW);
}

void m_adjust_left(){
    PWM_M1_WriteCompare(M1_FORWARD);
    PWM_M2_WriteCompare(STOP);
}

void m_adjust_right(){
    PWM_M1_WriteCompare(STOP);
    PWM_M2_WriteCompare(M2_FORWARD);
}

void m_turn_left(){
    PWM_M1_WriteCompare(M1_FORWARD);
    PWM_M2_WriteCompare(M2_BACKWARD);
}

void m_turn_right(){
    PWM_M1_WriteCompare(M1_BACKWARD);
    PWM_M2_WriteCompare(M2_FORWARD);
}










/* [] END OF FILE */
