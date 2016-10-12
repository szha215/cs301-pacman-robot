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

#include "RF_handler.h"
#include <math.h>

CY_ISR(rxISR){
    //TOGGLE_LED;
    char outChar = UART_GetChar();
    if (rx_recieved == 0){
        if (outChar == SOP && endCount < 2){
            endCount++;
        }else if (endCount >= 2){
            rxString[indexCount] = outChar;
            indexCount += 1;
            if (indexCount == 32){
                rx_recieved = 1;
            }
        }
    }
    
}
/*

CY_ISR(rxISR){
    //TOGGLE_LED;
    char outChar = UART_GetChar();
    if (rx_recieved == 0){
        if (outChar == '#'){
            rxString[0] = outChar;
        }else if (rxString[0] != 0){
            rxString[indexCount] = outChar;
            indexCount += 1;
            if (outChar == ']'){
                endCount++;
                if (endCount >= 4){
                    endCount = 0;
                    rx_recieved = 1;
                }
            }
        }
    }
    
}
*/

// define a new struct and init all struct values to 0 for all members
data_main* rf_Handler_init(){
    UART_Start();
    isrRF_RX_StartEx(rxISR);
    data_main* out = calloc(1,sizeof(data_main));
    return out;
}

straight_line_data* init_straight_line_data(uint16 distance,uint16 angle){
    straight_line_data* ret = calloc(1,sizeof(straight_line_data));
    //ret->distance_px = (uint16)(distance/100.0 * M_TO_PX_RATIO);
    ret->init_angle = angle;
    return ret;
}

void init_line_pos(straight_line_data* line_data_ptr,uint16 x, uint16 y,uint16 angle){
    line_data_ptr->init_x = x;
    line_data_ptr->init_y = y;
    line_data_ptr->init_angle = angle;
    init_x = x;
    init_y = y;
    init_angle = angle;
}


// decode the input string and allocate values into struct members
void handle_rx(char* in_string, data_main *out_struct)
{
    out_struct->rssi = (int8)in_string[0];
    out_struct->index = (uint8)in_string[1];
    out_struct->robot_xpos = (uint16)in_string[2] + (uint16)(in_string[3] << 8);
    out_struct->robot_ypos = (uint16)in_string[4]+ (uint16)(in_string[5] << 8);
    out_struct->robot_orientation = (uint16)in_string[6]+ (uint16)(in_string[7] << 8);
    out_struct->g0_xpos = (uint16)in_string[8]+ (uint16)(in_string[9] << 8);
    out_struct->g0_ypos = (uint16)in_string[10]+ (uint16)(in_string[11] << 8);
    out_struct->g0_speed = (uint16)in_string[12]+ (uint16)(in_string[13] << 8);
    out_struct->g0_direction = (uint16)in_string[14]+ (uint16)(in_string[15] << 8);
    out_struct->g1_xpos = (uint16)in_string[16]+ (uint16)(in_string[17] << 8);
    out_struct->g1_ypos = (uint16)in_string[18]+ (uint16)(in_string[19] << 8);
    out_struct->g1_speed = (uint16)in_string[20]+ (uint16)(in_string[21] << 8);
    out_struct->g1_direction = (uint16)in_string[22]+ (uint16)(in_string[23] << 8);
    out_struct->g2_xpos = (uint16)in_string[24]+ (uint16)(in_string[25] << 8);
    out_struct->g2_ypos = (uint16)in_string[26]+ (uint16)(in_string[27] << 8);
    out_struct->g2_speed = (uint16)in_string[28]+ (uint16)(in_string[29] << 8);
    out_struct->g2_direction = (uint16)in_string[30]+ (uint16)(in_string[31] << 8);
}


/*
/////// ASCII  ???????????????
// decode the input string and allocate values into struct members
void handle_rx(char* in_string, data_main *out_struct)
{
    uint8 j = 0;
    uint8 i = 1;
    char convChar[5];
    uint8 convIndex = 0;
    memset(convChar, 0, strlen(convChar));
    while (in_string[i] != '\n'){
        if (in_string[i] == ',' || in_string[i] == ']'){
            if (in_string[i - 1] != ']'){
                switch (j){
                    case 0:
                        out_struct->rssi = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 1:
                        out_struct->index = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 2:
                        out_struct->robot_xpos = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 3:
                        out_struct->robot_ypos = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 4:
                        out_struct->robot_orientation = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 5:
                        out_struct->g0_xpos = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 6:
                        out_struct->g0_ypos = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 7:
                        out_struct->g0_speed = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 8:
                        out_struct->g0_direction = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 9:
                        out_struct->g1_xpos = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 10:
                        out_struct->g1_ypos = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 11:
                        out_struct->g1_speed = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 12:
                        out_struct->g1_direction = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 13:
                        out_struct->g2_xpos = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 14:
                        out_struct->g2_ypos = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 15:
                        out_struct->g2_speed = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    case 16:
                        out_struct->g2_direction = atoi(convChar);
                        memset(convChar, 0, strlen(convChar));
                        break;
                    default:
                        break;
                }
                j++;
                convIndex = 0;
            }
        }else if (in_string[i] != '['){
            convChar[convIndex] = in_string[i];
            convIndex++;
        }
        i++;
    }
}
*/



void check_RF(data_main* RF_data){
    if (rx_recieved == 1){
        rxString[indexCount] = '\n';
        handle_rx(rxString, RF_data);
        memset(rxString, 0, sizeof(rxString));
        indexCount = 0;
        endCount = 0;
        rx_recieved = 0;
        rx_handled = 1;
    }
}


/*
void check_RF(data_main* RF_data){
    if (rx_recieved == 1){
        rxString[indexCount] = '\n';
        handle_rx(rxString, RF_data);
        memset(rxString, 0, sizeof(rxString));
        indexCount = 1;
        rx_recieved = 0;
        rx_handled = 1;
    }
}
*/



uint8 is_handled(){
    return rx_handled;   
}

void clear_handled(){
    rx_handled = 0;
}


//angle in rad
//distance is in px
uint16 get_target_x(uint16 init_X,uint16 distance,float angle){
    float dx;
    dx = cos(angle) * distance;
    return init_X + dx;
}

//angle in rad
//distance is in px
uint16 get_target_y(uint16 init_Y,uint16 distance,float angle){
    float dy;
    dy = sin(angle) * distance;
    return init_Y - dy;
}

//return 0 if on-line
//1 if needs to adjust right (on the left)
//2 if needs to adjust left (on the right)
uint8 check_current_x(straight_line_data* line_data_ptr,uint16 current_x,uint16 current_y){
    line_data_ptr->current_x = current_x;
    line_data_ptr->current_y = current_y;
    uint16 current_k;
    current_k = tan(line_data_ptr->init_angle) * line_data_ptr->current_x + line_data_ptr->init_y;
    if(current_y > current_k){
        return 1;
    }
    else if(current_y < current_k){
        return 2;
    }

    return 0;
}
//return 0 if on-line
//1 if needs to adjust right (on the left)
//2 if needs to adjust left (on the right)
uint8 check_current_y(data_main* data_main_ptr,straight_line_data* straight_line_data_ptr){
    uint16 current_y_pos = data_main_ptr->robot_ypos;
    uint16 current_angle_deg = data_main_ptr->robot_orientation;
    uint16 init_y = straight_line_data_ptr->init_y;
    uint16 init_angle = straight_line_data_ptr->init_angle;
    if(current_y_pos >= (init_y - Y_THRESHOLD) && current_y_pos <= (init_y + Y_THRESHOLD)){
        if(current_angle_deg <= (init_angle + ANGLE_THRESHOLD) && current_angle_deg >= (init_angle - ANGLE_THRESHOLD)){
            return NOT_ADJUSTING;
        }
        else if(current_angle_deg > init_angle){
            return ADJUST_RIGHT;
        }
        else if(current_angle_deg < init_angle){
            return ADJUST_LEFT;
        }
    }
    else if(current_y_pos > (init_y + Y_THRESHOLD)){
        return ADJUST_RIGHT;
    }
    else if(current_y_pos < (init_y - Y_THRESHOLD)){
        return ADJUST_LEFT;
    }
    return 0;
}

inline float deg_to_rad(float deg){
    return deg * M_PI / 1800.0;
}
/* [] END OF FILE */
