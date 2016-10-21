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

#include "motor_control.h"



void init_motor_control(){
    cmp_val_m1 = 150;
    cmp_val_m2 = 150;
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
    QuadDec_M1_Start();
    QuadDec_M2_Start();
    
}

motor_params* init_motor_params(uint8 predef_velocity, uint16 predef_distance){
    motor_params *motor_params = calloc(1,sizeof(motor_params));
    return motor_params;
}




// Converts centimeter per second velocity to number of quadrature counts per
// PID update period
uint8 conv_velocity(uint8 velocity){    //cm/s -> counts/50ms
    float counts;
    float velocity_mm;
    float timer_period;
    uint8 ret;
    velocity_mm = velocity * 10.0;
    

    timer_period = 20.0;
    counts = velocity_mm/(M_PI * WHEEL_DIAMETER) * COUNTS_PER_REV * COUNT_MODE; //counts/s
    counts = counts / timer_period; // counts per sample period
    ret = (uint8)counts;
    if(ret%2 != 0){
        ret++;
    }
    return (uint8)counts;
}


//distance in cm
//convert to quad_dec counts 
uint16 conv_distance(uint16 distance){
    static float distance_mm;
    static float counts;
    uint16 ret;
    distance_mm = distance * 10; // cm to mm
    counts = distance_mm/(M_PI * WHEEL_DIAMETER) * COUNTS_PER_REV * COUNT_MODE * 1.07; //mm to counts
    ret = (uint16)counts; //cast to uint16
    return ret;
}

//convert quad_dec counts to cm
uint16 conv_counts(uint16 counts){
    static float distance;
    distance = counts / (COUNTS_PER_REV * COUNT_MODE) * (M_PI * WHEEL_DIAMETER);
    distance /= 10;
    return (uint16)distance;
}


uint16 conv_pix_distance(uint16 distance){
    return distance * M_TO_PX_RATIO / 100 - 15;
}


void m_stop(){
    PWM_M1_WriteCompare(STOP_MOTOR);
    PWM_M2_WriteCompare(STOP_MOTOR);
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
    PWM_M1_WriteCompare(M1_FORWARD+2);
    PWM_M2_WriteCompare(STOP_MOTOR-1);
}

void m_adjust_right(){
    PWM_M1_WriteCompare(STOP_MOTOR-1);
    PWM_M2_WriteCompare(M2_FORWARD+1);
}

void rf_adjust_left(){
    PWM_M1_WriteCompare(M1_FORWARD);
    PWM_M2_WriteCompare(M2_FORWARD_SLOW);
}

void rf_adjust_right(){
    PWM_M1_WriteCompare(M1_FORWARD_SLOW);
    PWM_M2_WriteCompare(M2_FORWARD);
}

void m_turn_left(){
    PWM_M1_WriteCompare(M1_FORWARD+2);
    PWM_M2_WriteCompare(M2_BACKWARD-2);
}

void m_turn_right(){
    PWM_M1_WriteCompare(M1_BACKWARD-2);
    PWM_M2_WriteCompare(M2_FORWARD+2);
}



void m_straight_pid(){
    uint8 base_increment; 
    if(get_quad_dec_flag()){
        
        LED_Write(1);
        base_increment = BASE_INCREMENT;
        pid_calc_output(pid_controller_m1, quad_dec_m1_diff);
        pid_calc_output(pid_controller_m2, quad_dec_m2_diff);
        cmp_val_m1 += base_increment * pid_controller_m1->p_output;
        cmp_val_m2 += base_increment * pid_controller_m2->p_output;
        
        PWM_M1_WriteCompare(cmp_val_m1);
        PWM_M2_WriteCompare(cmp_val_m2);       
        set_quad_dec_flag(0);

    }

}



void set_quad_dec(int16 quad_m1, int16 quad_m2){
   quad_dec_m1_total = quad_m1;
   quad_dec_m2_total = quad_m2;
   quad_dec_m1_diff = quad_dec_m1_total -quad_dec_m1_prev;
   quad_dec_m2_diff = quad_dec_m2_total -quad_dec_m2_prev;
   quad_dec_m1_prev = quad_dec_m1_total;
   quad_dec_m2_prev = quad_dec_m2_total;
}

int16 get_quad_dec_m1(){
    return quad_dec_m1_diff;
}

int16 get_quad_dec_m2(){
    return quad_dec_m2_diff;
}

void set_quad_dec_flag(uint8 flag){
    quad_dec_done = flag;
}
uint8 get_quad_dec_flag(){
    return quad_dec_done;
}

/* [] END OF FILE */
