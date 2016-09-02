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
//#include "project.h"


// define a new struct and init all struct values to 0 for all members
data_main* rf_Handler_init(){
    data_main* out = malloc(sizeof(data_main));
    out->rssi = 0;
    out->index = 0;
    out->robot_xpos = 0;
    out->robot_ypos = 0;
    out->robot_orientation = 0;
    out->g0_xpos = 0;
    out->g0_ypos = 0;
    out->g0_speed = 0;
    out->g0_direction = 0;
    out->g1_xpos = 0;
    out->g1_ypos = 0;
    out->g1_speed = 0;
    out->g1_direction = 0;
    out->g2_xpos = 0;
    out->g2_ypos = 0;
    out->g2_speed = 0;
    out->g2_direction = 0;
    return out;
}

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

/* [] END OF FILE */
