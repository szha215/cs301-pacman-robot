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
static int16_t vertex_list[MAP_WIDTH*MAP_HEIGHT];
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
    CS.vertex_index = 0;

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
    clear_route(route, 400);
    clear_route(vertex_list, MAP_WIDTH*MAP_HEIGHT);
    //steps = find_path(state->level,map,route,495,663, food_packets[state->food_index][0],food_packets[state->food_index][1]);
    if (state->level == 1){
        steps = find_path(2,map,route,495,663, food_packetss[state->food_index][0],food_packetss[state->food_index][1]);
    }
    else if (state->level == 2){
        steps = find_path(state->level,map,route,495,663, food_packets[state->food_index][0],food_packets[state->food_index][1]);
    }
    else if(state->level == 4){
        
        state->vertex_list_length = get_vertex_list(route, steps, vertex_list);
        uint16_t x_cell = *(vertex_list + state->vertex_index) % MAP_WIDTH;
        uint16_t y_cell = *(vertex_list + state->vertex_index) / MAP_WIDTH;
        clear_route(route,400);

        steps = find_path(2,map,route,495,663,x_cell,y_cell);
    } else if(state->level == 3){
        int i;
        for(i = 0; i < 2; i++){
            // CyDelay(100);
            while(!is_handled()){check_RF(rf_data);}
            clear_handled();    
        }
        uint16_t x_cell = food_packetss[state->food_index][0];
        uint16_t y_cell = food_packetss[state->food_index][1];
        clear_route(route,400);
        steps = find_path_ghost(state->level, map, route, 
                        495, 663, x_cell, y_cell,
                        rf_data->g0_xpos, rf_data->g0_ypos,
                        rf_data->g1_xpos, rf_data->g1_ypos,
                        rf_data->g2_xpos, rf_data->g2_ypos);
    }



    state->current_decision = STRAIGHT;
    state->next_state = execute;

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

    check_RF(rf_data);
    if (state->level == 1){
        if(are_we_there_yet(rf_data->robot_xpos,rf_data->robot_ypos,food_packetss[state->food_index][0],food_packetss[state->food_index][1])){
            m_stop();
            if(state->food_index < 20){ 
                state->next_state = recalculate;
                state->current_decision = STOP;
            } else {
                state->current_decision = STOP;
                state->next_state = unknown;
            }
        } 
    } else if(state->level == 2){
        if(are_we_there_yet(rf_data->robot_xpos,rf_data->robot_ypos,food_packets[state->food_index][0],food_packets[state->food_index][1])){
            m_stop();
            if(state->food_index < 4){ 
                state->next_state = recalculate;
                state->current_decision = STOP;
            } else {
                state->current_decision = STOP;
                state->next_state = unknown;
            }
        } 
    } else if (state->level == 3){
        if(are_we_there_yet(rf_data->robot_xpos,rf_data->robot_ypos,food_packetss[state->food_index][0],food_packetss[state->food_index][1])){
            m_stop();
            if(state->food_index < 20){ 
                state->next_state = recalculate;
                state->current_decision = STOP;
            } else {
                state->current_decision = STOP;
                state->next_state = unknown;
            }
        } 
    }

    
}

void update(struct State* state,motion_type current_motion,data_main *rf_data){
    //update next instruction
    decision_type next_decision;
    int i;
     for(i = 0; i < 3; i++){
         CyDelay(50);
         while(!is_handled()){check_RF(rf_data);}
         clear_handled();    
     }


    
    if(state->level == 1){
        next_decision = next_turn(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,0);
        if(next_decision == OUT_OF_BOUNDS){//} || next_decision == ARRIVED){
            state->next_state = recalculate;
            state->current_decision = next_decision;
        } else {
            state->current_decision = next_decision;
            state->fsm_state = STATE_UPDATED;
            state->next_state = execute;
        }

    } else if(state->level == 2){
        next_decision = next_turn(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,0);
        if(next_decision == OUT_OF_BOUNDS){
            state->next_state = recalculate;
            state->current_decision = next_decision;
        } else {
            state->current_decision = next_decision;
            state->fsm_state = STATE_UPDATED;
            state->next_state = execute;
        }
    } else if(state->level == 3){
        if(state->current_decision != OUT_OF_BOUNDS){
            if(are_we_there_yet(rf_data->robot_xpos,rf_data->robot_ypos,food_packetss[state->food_index][0],food_packetss[state->food_index][1])){
                state->food_index = state->food_index + 1;
            }
        }

        //LED_Write(~LED_Read());
        clear_route(route,400);
       // decision_type next_decision;

        uint16_t x_cell = food_packetss[state->food_index][0];
        uint16_t y_cell = food_packetss[state->food_index][1];

        steps = find_path_ghost(state->level, map, route, 
                        rf_data->robot_xpos, rf_data->robot_ypos, x_cell, y_cell,
                        rf_data->g0_xpos, rf_data->g0_ypos,
                        rf_data->g1_xpos, rf_data->g1_ypos,
                        rf_data->g2_xpos, rf_data->g2_ypos);


        next_decision = next_turn(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,0);
        if(next_decision == OUT_OF_BOUNDS || next_decision == ARRIVED){
            state->next_state = recalculate;
            state->current_decision = next_decision;
        } else {
            state->current_decision = next_decision;
            state->fsm_state = STATE_UPDATED;
            state->next_state = execute;
        }

        //state->next_state = execute;
    }
        
}

void recalculate(struct State* state,motion_type current_motion,data_main *rf_data){

    
   
    while(!is_handled()){check_RF(rf_data);}
    clear_handled();    
   
    
    TOGGLE_LED;
    
    if(state->level == 1){
        int16_t next_vertex;
        if(state->current_decision != OUT_OF_BOUNDS){//} || state->current_decision == ARRIVED){
            //state->vertex_index = state->vertex_index + 1;
            state->food_index = state->food_index + 1;
        }
        clear_route(route,400);
        //next_vertex = *(vertex_list + state->vertex_index);   
        uint16_t x_cell = next_vertex % MAP_WIDTH;
        uint16_t y_cell = next_vertex / MAP_WIDTH;
        // LED_Write(1);
        //steps = find_path(2,map,route,rf_data->robot_xpos,rf_data->robot_ypos,x_cell,y_cell);
        steps = find_path(2,map,route,rf_data->robot_xpos, rf_data->robot_ypos, food_packetss[state->food_index][0],food_packetss[state->food_index][1]);
        state->next_state = update;

    }else if(state->level == 2){
        if(state->current_decision != OUT_OF_BOUNDS){
            state->food_index = state->food_index + 1;
        }

        //LED_Write(~LED_Read());
        clear_route(route,400);
       // decision_type next_decision;
        steps = find_path(2,map,route,rf_data->robot_xpos, rf_data->robot_ypos, food_packets[state->food_index][0],food_packets[state->food_index][1]);
        state->next_state = update;
    }else if(state->level == 3){
        if(state->current_decision != OUT_OF_BOUNDS){
            if(are_we_there_yet(rf_data->robot_xpos,rf_data->robot_ypos,food_packetss[state->food_index][0],food_packetss[state->food_index][1])){
                state->food_index = state->food_index + 1;
            }
        }
        decision_type next_decision;
        //LED_Write(~LED_Read());
        clear_route(route,400);
       // decision_type next_decision;

        uint16_t x_cell = food_packetss[state->food_index][0];
        uint16_t y_cell = food_packetss[state->food_index][1];

        steps = find_path_ghost(state->level, map, route, 
                        rf_data->robot_xpos, rf_data->robot_ypos, x_cell, y_cell,
                        rf_data->g0_xpos, rf_data->g0_ypos,
                        rf_data->g1_xpos, rf_data->g1_ypos,
                        rf_data->g2_xpos, rf_data->g2_ypos);


        next_decision = next_turn(route,steps,rf_data->robot_xpos,rf_data->robot_ypos,rf_data->robot_orientation,0);
        if(next_decision == OUT_OF_BOUNDS || next_decision == ARRIVED){
            state->next_state = recalculate;
            state->current_decision = next_decision;
        } else {
            state->current_decision = next_decision;
            state->fsm_state = STATE_UPDATED;
            state->next_state = execute;
        }
    }
   
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
