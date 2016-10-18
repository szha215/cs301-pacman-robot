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

static int16_t route[400];
static int16_t steps;


void init_FSM(){
    init_motion_actuator();
    
    set_pid_start(0);
}



void FSM(){
    struct State CS;
    struct motion_state motion_CS;
    init_FSM();
    motion_CS.next_state = motion_stop;
    CS.next_state = calculate;
    CS.count = 0;
    CS.step_counter = 0;
    CS.food_index = 0;
    data_main* rf_data;
    if(dip_read() < 4 && dip_read() > 0){
        CS.level = dip_read();    
    } else{
        return;
    }
    rf_data = rf_Handler_init();
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
    CyGlobalIntDisable;
    for(;;){
        TOGGLE_LED;
        CyDelay(1000);
    }
}

void calculate(struct State* state,motion_type current_motion,data_main *rf_data){
    //calculate the pathfind
    //maybe not needed for a star, but could still be needed in Level 1 or Level 3
    // state->rf_data = rf_Handler_init();
    // data_main* temp_rf_data;
    // temp_rf_data = state->rf_data;
    // int i;
    // for(i = 0; i < 2; i++){
    //     // CyDelay(100);
    //     while(!is_handled()){check_RF(rf_data);}
    //     clear_handled();    
    // }
    clear_route(route,400);
    // *(state->current_node) = conv_location(rf_data->robot_xpos,rf_data->robot_ypos);
    *(state->current_node) = conv_location(173,363);
    *(state->angle) = 0;
    // *(state->angle) = round_angle(rf_data->robot_orientation/10);
      // int16_t x, y, angl;

    // if (state->count == 0){
    //     x = 63;
    //     y = 361;
    //     angl = 0;
    //     state->count = state->count + 1;
    // } 


    //state->steps = find_path(2,map,route,x,y,1,3);
    
    // steps = find_path(2,map,route,63, 361, food_packets[state->food_index][0],food_packets[state->food_index][1]);
    steps = find_path(state->level,map,route,63,361, food_packets[state->food_index][0],food_packets[state->food_index][1]);
    
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
       // LED_Write(1);

       // for(;;){}
    //}

}

void execute(struct State* state,motion_type current_motion,data_main *rf_data){
    //execute current instruction, which is automatic in the sub FSM

    //if the robot is turning that means the current vertex has been visited
    //then update to the next instruction
    //should give some feedback to the outer path-find module which contains all the instruction
    
    check_RF(rf_data);
    if(current_motion == AT_INTERSECTION){
            state->next_state = update;
    }
    else if(current_motion == GOING_STRAIGHT){
        //LED_Write(1);
        state->fsm_state = STATE_IN_PROGRESS;
        //state->current_decision = STRAIGHT;
        state->next_state = execute;
    }


    if(state->level == 2){
        if(are_we_there_yet(rf_data->robot_xpos,rf_data->robot_ypos,food_packets[state->food_index][0],food_packets[state->food_index][1])){
            if(state->food_index < 4){ 
                state->next_state = recalculate;
                state->current_decision = STOP;
            } else {
                state->current_decision = STOP;
                state->next_state = unknown;
            }
        } 
    } else if(state->level == 1){
        // decision_type next_decision;
        // next_decision = next_turn(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,&(state->step_counter));
        // if(turn_around(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,&(state->step_counter))){
            // LED_Write(1);
        state->fsm_state = STATE_IN_PROGRESS;
        if(dfs_turn_around(route,steps,state->current_node,state->angle,&(state->step_counter))){
            state->fsm_state = WAIT_TURN_AROUND;
            state->next_state = update;
        } 
        
        // state->current_decision = next_decision;
        // state->next_state = execute;
    } else if(state->level == 3){
        state->current_decision = TURN_AROUND;
         
    }

    
}

void update(struct State* state,motion_type current_motion,data_main *rf_data){
    //update next instruction
    decision_type next_decision;
    // int i;
    // for(i = 0; i < 2; i++){
    //     CyDelay(50);
    //     while(!is_handled()){check_RF(rf_data);}
    //     clear_handled();    
    // }


    // if(are_we_there_yet(rf_data->robot_xpos,rf_data->robot_ypos,food_packets[state->food_index][0],food_packets[state->food_index][1])){
    //     if(state->food_index < 4){
    //         state->food_index = state->food_index + 1;     
    //         state->next_state = recalculate;
    //     } else {
    //         state->current_decision = STOP;
    //         state->next_state = unknown;
    //     }
    // } else {
    //     next_decision = next_turn(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,0);
    //     state->current_decision = next_decision;
    //     state->fsm_state = STATE_UPDATED;
    //     state->next_state = execute;
    // }
    
    
    if(state->level == 1){
        next_decision = dfs_next_turn(route,steps,state->current_node,state->angle,&(state->step_counter));
        state->current_decision = next_decision;
        state->fsm_state = STATE_UPDATED;
        state->next_state = execute;

    } else if(state->level == 2){
        next_decision = next_turn(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,0);
        if(next_decision == OUT_OF_BOUNDS){
            state->next_state = recalculate;
            state->current_decision = next_decision;
        } else{
            state->current_decision = next_decision;
            state->fsm_state = STATE_UPDATED;
            state->next_state = execute;
        }
    } else if(state->level == 3){

    }
    


    // state->current_decision = next_decision;
    // state->fsm_state = STATE_UPDATED;
    // state->next_state = execute;

    // int16_t x, y, angl;
    // if (state->count == 1){
    //     x = 173;
    //     y = 361;
    //     angl = 0;
        
    //     state->count = state->count +1;
    // } 
    // else if (state->count == 2){
    //     x = 173;
    //     y = 260;
    //     angl = 900;

    //     state->count = state->count +1;
    // } else if (state->count == 3){
    //     x = 65;
    //     y = 276;
    //     angl = 1800;
    //     state->count =  state->count +1;
    // }
    
}

void recalculate(struct State* state,motion_type current_motion,data_main *rf_data){

    int i;
    for(i = 0; i < 2; i++){
        CyDelay(50);
        while(!is_handled()){check_RF(rf_data);}
        clear_handled();    
    }
    if(state->current_decision != OUT_OF_BOUNDS){
        state->food_index = state->food_index + 1;

    }
    if (state->food_index == 4){
        LED_Write(~LED_Read());
    }

    //LED_Write(~LED_Read());
    clear_route(route,400);
   // decision_type next_decision;
    steps = find_path(2,map,route,rf_data->robot_xpos, rf_data->robot_ypos, food_packets[state->food_index][0],food_packets[state->food_index][1]);
    state->next_state = update;
    // next_decision = next_turn(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,0);
    // state->current_decision = next_decision;
    // state->fsm_state = STATE_UPDATED;
    // state->next_state = execute;
}



uint8 get_pid_start(){
    return pid_start;
}

void set_pid_start(uint8 start){
    pid_start = start;
}



uint8 dip_read(){
    uint8 output = 0x00; 
    
    // Active low switches
    output |= (DIP_0_Read() << 0) | (DIP_1_Read() << 1) | (DIP_2_Read() << 2) | (DIP_3_Read() << 3);
    
    return output;
}

/*

void foobar(struct State* state){


}

*/



/* [] END OF FILE */
