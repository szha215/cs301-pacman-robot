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
    CS.count = 0;
    data_main* rf_data;
    rf_data = rf_Handler_init();
    // while(!is_handled()){ check_RF(rf_data);}
    // clear_handled();
    //TODO:
    //Initialize all the motion and decision states 
    CS.current_decision = STOP;

    motion_CS.current_motion = STOPPED;

    CS.fsm_state = STATE_IN_PROGRESS;
    // CS <= NS; state updater
    for(;;){
        motion_CS.next_state(&motion_CS,CS.current_decision,CS.fsm_state);
        CS.next_state(&CS,motion_CS.current_motion,rf_data);
       
    }
}





void unknown(struct State* state,motion_type current_motion,data_main *rf_data){

}

void calculate(struct State* state,motion_type current_motion,data_main *rf_data){
    //calculate the pathfind
    //maybe not needed for a star, but could still be needed in Level 1 or Level 3
    // state->rf_data = rf_Handler_init();
    // data_main* temp_rf_data;
    // temp_rf_data = state->rf_data;
    // while(!is_handled()){ check_RF(rf_data);}
    // clear_handled();
    clear_route(route,285);

    int16_t x, y, angl;

    if (state->count == 0){
        x = 63;
        y = 361;
        angl = 0;
        state->count = state->count + 1;
    } 


//    state->steps = find_path(2,&map,state->route,rf_data->robot_xpos,rf_data->robot_ypos,food_packets[0][0],food_packets[0][1]);
    steps = find_path(2,map,route, x, y, 55,55);
    // state->steps = find_path(2,*map,state->route,63,380,food_packets[0][0],food_packets[0][1]);
    state->current_decision = STRAIGHT;
    state->next_state = execute;
    // char tempString[BUF_SIZE];
    // for(;;){
    //     sprintf(tempString,"\r\n start X: %d\r\n",rf_data->robot_xpos); usbPutString(tempString);
    //     sprintf(tempString,"\r\n start Y: %d\r\n",rf_data->robot_ypos); usbPutString(tempString);
    //     sprintf(tempString,"\r\n start Angle: %d\r\n",rf_data->robot_orientation); usbPutString(tempString);
    //     sprintf(tempString,"\r\n ===================\r\n"); usbPutString(tempString);

    // }
   // if(state->steps == -2){
       LED_Write(1);
    //}

}

void execute(struct State* state,motion_type current_motion,data_main *rf_data){
    //execute current instruction, which is automatic in the sub FSM

    //if the robot is turning that means the current vertex has been visited
    //then update to the next instruction
    //should give some feedback to the outer path-find module which contains all the instruction
    if(current_motion == AT_INTERSECTION){
        state->next_state = update;
    }
    else if(current_motion == GOING_STRAIGHT){
        //LED_Write(1);
        state->fsm_state = STATE_IN_PROGRESS;
        //state->current_decision = STRAIGHT;
        state->next_state = execute;
    }
}

void update(struct State* state,motion_type current_motion,data_main *rf_data){
    //update next instruction
    decision_type next_decision;
    // while(!is_handled()){check_RF(rf_data);}
    // clear_handled();
    int16_t x, y, angl;
    if (state->count == 1){
        x = 173;
        y = 361;
        angl = 0;
        // LED_Write(1);
        state->count = state->count +1;
    } else if (state->count == 2){
        x = 173;
        y = 260;
        angl = 900;
        state->count = state->count +1;
    } else if (state->count == 3){
        x = 65;
        y = 276;
        angl = 1800;
        state->count =  state->count +1;
    }

//    next_decision = next_turn(state->route,state->steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation);
    next_decision = next_turn(route,steps, x, y,angl);
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
