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

#include "FSM.h"

CY_ISR(isr_s_fl){
    s_fl = S_FL_Read();
    s_fr = S_FR_Read();
}

CY_ISR(isr_s_fr){
    s_fr = S_FR_Read();
    s_fl = S_FL_Read();
}

CY_ISR(isr_s_l){
    s_l = S_L_Read();
    s_r = S_R_Read();
}

CY_ISR(isr_s_r){
    s_r = S_R_Read();
    s_l = S_L_Read();
}

CY_ISR(isr_s_b){
    s_b = S_B_Read();
}

CY_ISR(isr_s_m){
    s_m = S_M_Read();
}

CY_ISR(isr_button){
    button_flag = 1;
}

void init_FSM(){
    init_motor_control();
    start_sensor_isr();
}

void start_sensor_isr(){
    ISR_S_FL_StartEx(isr_s_fl);
    ISR_S_FR_StartEx(isr_s_fr);
    ISR_S_L_StartEx(isr_s_l);
    ISR_S_R_StartEx(isr_s_r);
    ISR_S_M_StartEx(isr_s_m);
    ISR_S_B_StartEx(isr_s_b);
}

void FSM(){
    struct State CS = {straight};

    init_FSM();

    // CS <= NS; state updater
    for(;;){
        CS.next_state(&CS);
    }
}



void unknown(struct State* state){
    m_stop();
	LED_Write(1);
}

void straight(struct State* state){
    m_straight_slow();
    
    if (s_fl == IN_LINE && s_fr == IN_LINE){
        state->next_state = straight;
    } else if (s_fl == OUT_LINE && s_fr == IN_LINE) {
        state->next_state = adjust_right;
    } else if (s_fr == OUT_LINE && s_fl == IN_LINE) {
        state->next_state = adjust_left;
    } else if (s_fr == OUT_LINE && s_fl == OUT_LINE) {
        state->next_state = front_out;

    }
    
}

// Corner or end T, where front 2 sensors go out
void front_out(struct State* state){
    LED_Write(1);
    m_straight_slow();

    state->next_state = intersection;
    
}

// Cross intersection or side T
void intersection(struct State* state){

    if(s_l == IN_LINE && s_r == OUT_LINE){
        state->next_state = turn_left;
    }
    else if(s_l == OUT_LINE && s_r == IN_LINE){
        state->next_state = turn_right;
    }
    else{
        state->next_state = front_out;
    }
}

void turn_left(struct State* state){
    m_turn_left();

    if (s_fr == IN_LINE && s_fl == IN_LINE){
        state->next_state = straight;
    } else{

        state->next_state = turn_left;
    }
}

void turn_right(struct State* state){
    m_turn_right();

    if(s_fr == IN_LINE && s_fl == IN_LINE){
        state->next_state = straight;
    }
    else{
        state->next_state = turn_right;
    }
}

void adjust_right(struct State* state){
    m_adjust_right();

    if (s_fl == IN_LINE && s_fr == IN_LINE){
        state->next_state = straight;
    } else if (s_fl == OUT_LINE && s_fr == IN_LINE) {
        state->next_state = adjust_right;
    } else if (s_fr == OUT_LINE && s_fl == IN_LINE) {
        state->next_state = adjust_left;
    } else if (s_fr == OUT_LINE && s_fl == OUT_LINE) {
        state->next_state = front_out;
    }

}

void adjust_left(struct State* state){
    m_adjust_left();

    if (s_fl == IN_LINE && s_fr == IN_LINE){
        state->next_state = straight;
    } else if (s_fl == OUT_LINE && s_fr == IN_LINE) {
        state->next_state = adjust_right;
    } else if (s_fr == OUT_LINE && s_fl == IN_LINE) {
        state->next_state = adjust_left;
    } else if (s_fr == OUT_LINE && s_fl == OUT_LINE) {
        state->next_state = front_out;
    }

}








/*

void foobar(struct State* state){


}

*/



/* [] END OF FILE */
