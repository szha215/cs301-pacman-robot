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
    clear_handled();
    data_main* out = calloc(1,sizeof(data_main));
    return out;
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
/* [] END OF FILE */
