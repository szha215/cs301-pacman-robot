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

#include <stdio.h>
#include <stdlib.h>

#include "project.h"
#include "RF_Handler.h"
#include "motor_control.h"
#include "FSM.h"
#include "USB_UART.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~
//TECH TEST 2 PARAMETERS
//DEFINED DISTANCE(CM) AND VELOCITY(CM/S)
#define PREDEF_DISTANCE 100
#define PREDEF_VELOCTIY 15




#define TOGGLE_LED LED_Write(~LED_Read())
#define IN_LINE 1
#define OUT_LINE 0

//* ========================================

//#define RXSTRINGSIZE 255

#define FALSE 0
#define TRUE 1


//-------------
//ISR vars
uint8 start = 0;
uint8 timer_50ms_counts= 0;

//-------------
//DIP readings
uint8 dip_read();





int i = 0;
uint8 int_en = 0;

//-------------
//PWM varss
pid_params* pid_controller_m1;
pid_params* pid_controller_m2;



//-------------
//Quad_dec vars 
int16 quad_dec_m1 = 0;
int16 quad_dec_m2 = 0;


//* ========================================
// RF globals

//-------------
//helper functions
void sensor_init();
void s_interrupts_enable();

//* ========================================


uint8 isr_disabled = 0;
uint8 fsm_flag = 0;

//==========================================
//ADC
uint16 adc_val = 0;
uint8 adc_cnt = 0;

CY_ISR(adcISR){
    adc_val = ADC_SAR_1_GetResult16();
    TOGGLE_LED;   
    adc_cnt = 1;
}

//=========================================





CY_ISR(isr_s_timer){
    
}

//------------
//SENSOR ISR READINGS


int16_t* func(void){
    return malloc(285*5*sizeof(int16_t));
}


int main()
{
	
    //CyDelay(1000);
    
   // uint8 dip_val = 0x00;

	
    CyGlobalIntEnable;

   
    
    //char tempString[BUF_SIZE];
    
    //dip_val = dip_read();
    
    USBUART_Start(0,USBUART_5V_OPERATION);


    // for(;;){}

    //if(dip_val == 1){
    CyDelay(1000);
    FSM();
    //}

    data_main* RF_data;
    RF_data = rf_Handler_init();   
   
    char tempString[BUF_SIZE];
    // Something critical happened if the program gets here
    for(;;)
    {   
        TOGGLE_LED;
        CyDelay(500);
        check_RF(RF_data);
        if(is_handled()){
            TOGGLE_LED;
            sprintf(tempString,"\r\n ~ rssi: %d\r\n", RF_data->rssi); usbPutString(tempString);
            sprintf(tempString," ~ index: %d\r\n", RF_data->index); usbPutString(tempString);
            
            sprintf(tempString," ~ robot x pos: %d\r\n", RF_data->robot_xpos); usbPutString(tempString);
            sprintf(tempString," ~ robot y pos: %d\r\n", RF_data->robot_ypos); usbPutString(tempString);
            sprintf(tempString," ~ robot angle: %d\r\n\n", RF_data->robot_orientation); usbPutString(tempString);

            sprintf(tempString," ~ ghost0 x pos: %d\r\n", RF_data->g0_xpos); usbPutString(tempString);
            sprintf(tempString," ~ ghost0 y pos: %d\r\n", RF_data->g0_ypos); usbPutString(tempString);
            sprintf(tempString," ~ ghost0 speed: %d\r\n", RF_data->g0_speed); usbPutString(tempString);
            sprintf(tempString," ~ ghost0 direction: %d\r\n", RF_data->g0_direction); usbPutString(tempString);

            sprintf(tempString," ~ ghost1 x pos: %d\r\n", RF_data->g1_xpos); usbPutString(tempString);
            sprintf(tempString," ~ ghost1 y pos: %d\r\n", RF_data->g1_ypos); usbPutString(tempString);
            sprintf(tempString," ~ ghost1 speed: %d\r\n", RF_data->g1_speed); usbPutString(tempString);
            sprintf(tempString," ~ ghost1 direction: %d\r\n", RF_data->g1_direction); usbPutString(tempString);

            sprintf(tempString," ~ ghost2 x pos: %d\r\n", RF_data->g2_xpos); usbPutString(tempString);
            sprintf(tempString," ~ ghost2 y pos: %d\r\n", RF_data->g2_ypos); usbPutString(tempString);
            sprintf(tempString," ~ ghost2 speed: %d\r\n", RF_data->g2_speed); usbPutString(tempString);
            sprintf(tempString," ~ ghost2 direction: %d\r\n\n", RF_data->g2_direction); usbPutString(tempString);
            clear_handled();
        }
        
        

    }
}


void sensor_init(){
    s_fr = S_FR_Read();
    s_fl = S_FL_Read();
    s_m = S_M_Read();
    s_l = S_L_Read();
    s_r = S_R_Read();
    s_b = S_B_Read();
}



void s_interrupts_enable(){
    if (int_en == 0){
        // ISR_S_FL_StartEx(isr_s_fl);
        // ISR_S_FR_StartEx(isr_s_fr);
        // ISR_S_L_StartEx(isr_s_l);
        // ISR_S_R_StartEx(isr_s_r);
        // ISR_S_M_StartEx(isr_s_m);
        // ISR_S_B_StartEx(isr_s_b);   
        // //isr_s_timer_Stop();
        // isr_s_timer_Disable();
    }
    
    int_en = 1;
}




