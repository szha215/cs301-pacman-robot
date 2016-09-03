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

#ifndef VBAT_ADC_H
#define VBAT_ADC_H

#include "project.h"

extern uint16 adc_val;
    
void init_vbat_adc();
void start_adc();
void stop_adc();
float get_v_bat();

#endif
/* [] END OF FILE */
