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
    CS.next_state = execute;
    init_FSM();

    
    //TODO:
    //Initialize all the motion and decision states 
    CS.current_decision = STOP;
    motion_CS.current_motion = STOPPED;
    //decision flag of pathfinding results
    decision_type decision = STOP; //pathfind variable

    // CS <= NS; state updater
    for(;;){
        motion_CS.next_state(&motion_CS,CS.current_decision);
        CS.next_state(&CS,motion_CS.current_motion,decision);
       
    }
}





void unknown(struct State* state,motion_type current_motion,decision_type decision_input){

}

void calculate(struct State* state,motion_type current_motion,decision_type decision_input){
    //calculate the pathfind
    //maybe not needed for a star, but could still be needed in Level 1 or Level 3
}

void execute(struct State* state,motion_type current_motion,decision_type decision_input){
    //execute current instruction, which is automatic in the sub FSM

    //if the robot is turning that means the current vertex has been visited
    //then update to the next instruction
    //should give some feedback to the outer path-find module which contains all the instruction
    if(current_motion == TURNING){
        state->next_state = update;
    }
}

void update(struct State* state,motion_type current_motion,decision_type decision_input){
    //update next instruction
    state->current_decision = decision_input;
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
