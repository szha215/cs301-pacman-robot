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




void init_FSM(){
    init_motion_actuator();
    set_pid_start(0);
}



void FSM(){
    struct State CS;
    struct motion_state motion_CS;
    motion_CS.next_state = motion_straight;
    CS.next_state = straight;
    init_FSM();
   
    
    // CS <= NS; state updater
    for(;;){
        motion_CS.next_state(&motion_CS,CS.current_flag);
        CS.next_state(&CS,motion_CS.current_flag);
       
    }
}





void unknown(struct State* state,uint8 flag){
    m_stop();

}

void straight(struct State* state,uint8 flag){

    
}


// Corner or end T, where front 2 sensors go out
void front_out(struct State* state,uint8 flag){
    //LED_Write(1);
    m_straight_slow();

    state->next_state = corner;
    // if(s_l == IN_LINE && s_r == IN_LINE){
    //     state->next_state = t_intersection_front;
    // } else if (s_l == IN_LINE || s_r == IN_LINE){
    //     state->next_state = corner;
    // } else {
    //     state->next_state = front_out;
    // }
    
}

// Corner
void corner(struct State* state,uint8 flag){

    if(s_l == IN_LINE && s_r == OUT_LINE){
        state->next_state = turn_left;
    } else if (s_l == OUT_LINE && s_r == IN_LINE){
        state->next_state = turn_right;
    } else {
        state->next_state = front_out;
    }
}
void t_intersection_front(struct State* state,uint8 flag){
    m_stop();
    
}

void t_intersection_left(struct State* state,uint8 flag){
    
}

void t_intersection_right(struct State* state,uint8 flag){
    
}

void x_intersection(struct State* state,uint8 flag){
    LED_Write(1);

    state->next_state = straight;
}

void turn_left(struct State* state,uint8 flag){
    m_turn_left();

    if (s_fr == IN_LINE && s_fl == IN_LINE){
        state->next_state = straight;
    } else{

        state->next_state = turn_left;
    }
}

void turn_left_prep(struct State* state,uint8 flag){
    m_turn_left();

    if (s_fl == OUT_LINE){
        state->next_state = turn_left;
     //   state->turned = 1;
    } else {
        state->next_state = turn_left_prep;
    }
}

void turn_right(struct State* state,uint8 flag){
    m_turn_right();

    if(s_fr == IN_LINE && s_fl == IN_LINE){
        state->next_state = straight;
    }
    else{
        state->next_state = turn_right;
    }
}

void adjust_right(struct State* state,uint8 flag){
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

void adjust_left(struct State* state,uint8 flag){
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




uint8 get_pid_start(){
    return pid_start;
}

void set_pid_start(uint8 start){
    pid_start = start;
}




/*

void foobar(struct State* state){


}

*/



/* [] END OF FILE */
