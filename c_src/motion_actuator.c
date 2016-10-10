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

/* [] END OF FILE */

#include "motion_actuator.h"


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


void init_motion_actuator(){
	start_sensor_isr();
	init_motor_control();
}

void start_sensor_isr(){
    ISR_S_FL_StartEx(isr_s_fl);
    ISR_S_FR_StartEx(isr_s_fr);
    ISR_S_L_StartEx(isr_s_l);
    ISR_S_R_StartEx(isr_s_r);
    ISR_S_M_StartEx(isr_s_m);
    ISR_S_B_StartEx(isr_s_b);
}


void motion_straight(struct motion_state* m_state,decision_type decision){
    m_state->current_motion = STRAIGHT;
	m_straight();

    if(decision == STRAIGHT){
        m_state->next_state = motion_straight;
    }
    else if(decision == TURN_LEFT){
        if(s_l == IN_LINE){
            if(s_fr == IN_LINE || s_fl == IN_LINE){
                //intersection, go to turning buffer
                m_state->next_state = motion_turning_buffer;
            }
            else if(s_fr == OUT_LINE && s_fl == OUT_LINE){
                //not intersection, go to turning state
                m_state->next_state = motion_turn_left;
            }
        }
        else{
            //keep going
            m_state->next_state = motion_straight;
        }

    }
    else if(decision == TURN_RIGHT){
        if(s_r == IN_LINE){
            if(s_fr == IN_LINE || s_fl == IN_LINE){
                //intersection, go to turning buffer
                m_state->next_state = motion_turning_buffer;
            }
            else if(s_fr == OUT_LINE && s_fl == OUT_LINE){
                //not intersection, go to turning state
                m_state->next_state = motion_turn_right;
            }
        }
        else{
            //keep going
            m_state->next_state = motion_straight;
        }
    }
    else if(decision == TURN_AROUND){

    }
    else if(decision == STOP){
        m_state->next_state = motion_stop;
    }    


    //straight
    if (s_fl == IN_LINE && s_fr == IN_LINE){
        m_state->next_state = motion_straight;
        
    // adjust right
    } else if (s_fl == OUT_LINE && s_fr == IN_LINE) {
        m_state->next_state = motion_adjust_right;
        
    // adjust left
    } else if (s_fr == OUT_LINE && s_fl == IN_LINE) {
        m_state->next_state = motion_adjust_left;
    } 

}

void motion_adjust_left(struct motion_state* m_state,decision_type decision){
    m_state->current_motion = ADJUSTING;
	m_adjust_left();

    if (s_fl == IN_LINE && s_fr == IN_LINE){
        m_state->next_state = motion_straight;
    } else if (s_fl == OUT_LINE && s_fr == IN_LINE) {
        m_state->next_state = motion_adjust_right;
    } else if (s_fr == OUT_LINE && s_fl == IN_LINE) {
        m_state->next_state = motion_adjust_left;
    } else if (s_fr == OUT_LINE && s_fl == OUT_LINE) {
        m_state->next_state = motion_stop;
    }
}

void motion_adjust_right(struct motion_state* m_state,decision_type decision){
    m_state->current_motion = ADJUSTING;
	m_adjust_right();

    if (s_fl == IN_LINE && s_fr == IN_LINE){
        m_state->next_state = motion_straight;
    } else if (s_fl == OUT_LINE && s_fr == IN_LINE) {
        m_state->next_state = motion_adjust_right;
    } else if (s_fr == OUT_LINE && s_fl == IN_LINE) {
        m_state->next_state = motion_adjust_left;
    } else if (s_fr == OUT_LINE && s_fl == OUT_LINE) {
        m_state->next_state = motion_stop;
    }
}

void motion_stop(struct motion_state* m_state,decision_type decision){
    m_state->current_motion = STOPPED;
	m_stop();
}


void motion_turn_left(struct motion_state* m_state,decision_type decision){
    if(s_fr == IN_LINE && s_fl == IN_LINE){
        m_state->next_state = motion_straight;
    }
    else{
        m_turn_left();
    }
}

void motion_turn_right(struct motion_state* m_state,decision_type decision){
    if(s_fr == IN_LINE && s_fl == IN_LINE){
        m_state->next_state = motion_straight;
    }
    else{
        m_turn_right();
    }
}

void motion_turn_around(struct motion_state* m_state,decision_type decision){

}

void motion_turning_buffer(struct motion_state* m_state,decision_type decision){
//this is the state that will handle the intersection turning or any other states that needs a intermediate buffer
    m_state->current_motion = TURNING;

    if(decision == TURN_LEFT){
        if(s_fr == OUT_LINE && s_fl == OUT_LINE){
            m_state->next_state = motion_turn_left;
        }
        else{
            m_turn_left();
            m_state->next_state = motion_turning_buffer;
        }
    }
    else if(decision == TURN_RIGHT){
        if(s_fr == OUT_LINE && s_fl == OUT_LINE){
            m_state->next_state = motion_turn_right;
        }
        else{
            m_turn_right();
            m_state->next_state = motion_turning_buffer;
        }
    }
    else if(decision == TURN_AROUND){

    }

}


uint8 receive_next_state(decision_type decision){
	return 0;
}

uint8 get_state_complete(){
	return 0;
}


