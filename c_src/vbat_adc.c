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

#include <vbat_adc.h>

CY_ISR(adc_isr){
    adc_val = ADC_SAR_1_GetResult16();
}

void init_vbat_adc(){
    isr_eoc_StartEx(adc_isr);
    ADC_SAR_1_IRQ_Enable();
    ADC_SAR_1_Start();
    start_adc();
}

void start_adc(){
    ADC_SAR_1_StartConvert();
}

void stop_adc(){
    ADC_SAR_1_StopConvert();
}

float get_v_bat(){
    return (((float)adc_val) * 0.001220703125) / 0.26666;;
}

/* [] END OF FILE */
