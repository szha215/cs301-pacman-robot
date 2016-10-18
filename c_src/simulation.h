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


#ifndef SIMULATION_H
#define SIMULATION_H

/* This is deliberately blank, as it acts as a flag for the compiler.
   If this file is included, the compiler will add in the printf lines used
   for routing testing/simulations. It also avoids PSoC specific functions 
   defined in project.h which are not available to statndard GCC compiler.

   eg.
   #ifdef SIMULATION_H
   		printf("counter = %i", counter);
   #endif

   eg2.
   #ifndef SIMULATION_H
   		#include "project.h"
   #endif

   When programming the PSoC, the #include for this file should be commented out.
*/

#endif