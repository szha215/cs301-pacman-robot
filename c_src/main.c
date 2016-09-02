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
#include "PID_control.h"
#include "RF_Handler.h"
#include "FSM.h"
#include "motor_control.h"


#define TOGGLE_LED LED_Write(~LED_Read())
#define IN_LINE 1
#define OUT_LINE 0

//* ========================================
#define PACKETSIZE 32
#define RXSTRINGSIZE 255

#define FALSE 0
#define TRUE 1

#define BUF_SIZE 64 // USBUART fixed buffer size

#define CHAR_NULL '0'
#define CHAR_BACKSP 0x08
#define CHAR_DEL 0x7F
#define CHAR_ENTER 0x0D
#define LOW_DIGIT '0'
#define HIGH_DIGIT '9'

#define SOP 0xaa
char entry[BUF_SIZE];
//-------------
//PID vars
#define DESIRED_COUNTS 32
uint16 base_increment_val = 25;
pid_params* pid_controller_m1;
pid_params* pid_controller_m2;
uint8 pwm_start =0;
uint8 pwm_stop =0;


//-------------
//ISR vars
uint8 start = 0;
uint8 compared = 0;
uint8 timer_50ms_count = 0;

//-------------
//DIP readings
uint8 dip_read();

//-------------
//Sensor vars
uint8 s_fl = 0;
uint8 s_fr = 0;
uint8 s_l = 0;
uint8 s_r = 0;
uint8 s_m = 0;
uint8 s_b = 0;
#define NOT_TURNING 0
#define LEFT_TURN 1
#define RIGHT_TURN 2
#define ABOUT_TO_TURN 3
uint8 TURN_DIR = NOT_TURNING;


int i = 0;
uint8 int_en = 0;
uint8 button_flag = 0;
//-------------
//PWM vars

uint8 compare_val_m1 = 215;
uint8 compare_val_m2 = 230;

//-------------
//Quad_dec vars 
int16 quad_dec_m1 = 0;
int16 quad_dec_m2 = 0;


//* ========================================
// RF globals
data_main* system_state;
uint8 indexCount = 0;
uint8 endCount = 0;
char rxString[RXSTRINGSIZE];
uint8 rx_recieved = 0;

//-------------
//helper functions
void sensor_init();
void s_interrupts_enable();

//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();

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

CY_ISR(rxISR){
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

CY_ISR(timer_isr){
    
	if(start == 0){
		PWM_M2_WriteCompare(STOP);
		PWM_M1_WriteCompare(STOP);
        //dip_val = dip_read();
        //change the start value depending on the dip switch pos???
		start = 1;
	}
    
    quad_dec_m1 = QuadDec_M1_GetCounter();
    quad_dec_m2 = QuadDec_M2_GetCounter();
    
    QuadDec_M1_SetCounter(0);
    QuadDec_M2_SetCounter(0);
    compared = 1;
    
    timer_50ms_count++;

}

CY_ISR(isr_s_timer){
    if (start == 1){
        s_fl = S_FL_Read();
        s_fr = S_FR_Read();
        s_m = S_M_Read();
        s_b = S_B_Read();
    }
}

//------------
//SENSOR ISR READINGS


int main()
{
	uint8 dip_val = 0x00;



	CyDelay(1000);
    CyGlobalIntEnable;


    //=========================
    // USB and UART initialize
    //USBUART_Start(0,USBUART_5V_OPERATION);
    //UART_Start();
    
    // used to print to PuTTY
    //char tempString[BUF_SIZE];
    // rf and rfISR initialize
    //system_state = rf_Handler_init();
    

    //=========================
    //ADC
    
    //float v_bat = 0.0;
    //=========================



    //QuadDec_M1_Start();
    //QuadDec_M2_Start();
    
    //pid_controller_m1 = pid_init(0.05,DESIRED_COUNTS);
   // pid_controller_m2 = pid_init(0.05,DESIRED_COUNTS);

    //CyDelay(1000);
    Timer_TS_Start();
    //Timer_1_Start();
    //PWM_M2_Start();
    //PWM_M1_Start();
    
    isr_TS_StartEx(timer_isr);
    //isr_s_timer_StartEx(isr_s_timer);
    // ISR_S_FL_StartEx(isr_s_fl);
    // ISR_S_FR_StartEx(isr_s_fr);
    // ISR_S_L_StartEx(isr_s_l);
    // ISR_S_R_StartEx(isr_s_r);
    // ISR_S_M_StartEx(isr_s_m);
    // ISR_S_B_StartEx(isr_s_b);
    //sensor_init();
    
    //isr_button_StartEx(isr_button);
    
    dip_val = dip_read();

   	//dip_val = 0b00001110;

    if (dip_val == 1){
        FSM();
    }

    switch(dip_val){
    	// case 8:	// open loop

    	// 	break;

    	// case 4:

    	// 	break;

    	// OFF ON ON ON
    	case 14:	// Maze
    		//FSM();
    		break;
    }
    
    
    
    
    
    // Something critical happened if the program gets here
    for(;;)
    {   
        TOGGLE_LED;
        CyDelay(500);
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

uint8 dip_read(){
    uint8 output = 0x00; 
    
    // Active low switches
    output |= (DIP_0_Read() << 0) | (DIP_1_Read() << 1) | (DIP_2_Read() << 2) | (DIP_3_Read() << 3);
    
    return output;
}


void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')
    
    while (USBUART_CDCIsReady() == 0);
    s[63]='\0';
    s[62]='!';
    USBUART_PutData((uint8*)s,strlen(s));
}
//* ========================================
void usbPutChar(char c)
{
    while (USBUART_CDCIsReady() == 0);
    USBUART_PutChar(c);
}


//* ========================================
void handle_usb()
{
    
    // handles input at terminal, echos it back to the terminal
    // turn echo OFF, key emulation: only CR
    // entered string is made available in 'rxString' and 'rx_recieved' is set
    
    static uint8 usbStarted = FALSE;
    static uint16 usbBufCount = 0;
    uint8 c; 
    

    if (!usbStarted)
    {
        if (USBUART_GetConfiguration())
        {
            USBUART_CDC_Init();
            usbStarted = TRUE;
        }
    }
    else
    {
        if (USBUART_DataIsReady() != 0)
        {  
            c = USBUART_GetChar();
            if ((c == 13) || (c == 10))
            {
                entry[usbBufCount]= '\0';
                strcpy(rxString,entry);
                usbBufCount = 0;
                rx_recieved = 1;
            }
            else 
            {
                if (((c == CHAR_BACKSP) || (c == CHAR_DEL) ) && (usbBufCount > 0) )
                    usbBufCount--;
                else
                    entry[usbBufCount++] = c;  
            }
        }
    }     
}