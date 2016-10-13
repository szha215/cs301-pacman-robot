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


#ifndef USB_UART_H
#define USB_UART_H
#include <stdio.h>
#include <stdlib.h>

#include "project.h"
#include "RF_Handler.h"
#define PACKETSIZE 32
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
void usbPutString(char *s);
void usbPutChar(char c);




#endif
/* [] END OF FILE */
