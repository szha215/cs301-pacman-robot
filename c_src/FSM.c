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
    m_stop();

}

void straight(struct State* state,motion_type current_motion,decision_type decision_input){

}



void turn_left(struct State* state,motion_type current_motion,decision_type decision_input){
    
}



void turn_right(struct State* state,motion_type current_motion,decision_type decision_input){
    
}


void turn_around(struct State* state,motion_type current_motion,decision_type decision_input){

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
