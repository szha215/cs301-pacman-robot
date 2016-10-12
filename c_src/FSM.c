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
    motion_CS.next_state = motion_stop;
    CS.next_state = calculate;
    init_FSM();


    //TODO:
    //Initialize all the motion and decision states 
    CS.current_decision = STOP;

    motion_CS.current_motion = STOPPED;

    CS.fsm_state = STATE_IN_PROGRESS;
    // CS <= NS; state updater
    for(;;){
        motion_CS.next_state(&motion_CS,CS.current_decision,CS.fsm_state);
        CS.next_state(&CS,motion_CS.current_motion);
       
    }
}





void unknown(struct State* state,motion_type current_motion){

}

void calculate(struct State* state,motion_type current_motion){
    //calculate the pathfind
    //maybe not needed for a star, but could still be needed in Level 1 or Level 3
    state->rf_data = rf_Handler_init();

    while(!is_handled()){ check_RF(state->rf_data);}
    clear_handled();
    state->route = calloc(285,sizeof(int16_t));
    state->steps = find_path(2,*map,state->route,state->rf_data->robot_xpos,state->rf_data->robot_ypos,food_packets[0][0],food_packets[0][1]);
    state->current_decision = STRAIGHT;
    state->next_state = execute;


}

void execute(struct State* state,motion_type current_motion){
    //execute current instruction, which is automatic in the sub FSM

    //if the robot is turning that means the current vertex has been visited
    //then update to the next instruction
    //should give some feedback to the outer path-find module which contains all the instruction
    
    if(current_motion == AT_INTERSECTION){
        state->next_state = update;
    }
    else if(current_motion == GOING_STRAIGHT){
        LED_Write(1);
        state->fsm_state = STATE_IN_PROGRESS;
        //state->current_decision = STRAIGHT;
        state->next_state = execute;
    }
}

void update(struct State* state,motion_type current_motion){
    //update next instruction
    decision_type next_decision;
    while(!is_handled()){check_RF(state->rf_data);}
    clear_handled();
    
    next_decision = next_turn(state->route,state->steps,state->rf_data->robot_xpos,state->rf_data->robot_ypos,state->rf_data->robot_orientation);
    
    state->current_decision = next_decision;
    state->fsm_state = STATE_UPDATED;
    state->next_state = execute;
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
