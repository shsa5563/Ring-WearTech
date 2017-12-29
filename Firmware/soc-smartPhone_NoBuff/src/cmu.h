/***********************************************************************************************//**
* File Name        : cmu.h
* File Description : This file contains the declaration of the function used to initialize the clock
*                    for the MCU for the Blue Gecko based on the Energy Mode selected
* Author           : Srishti Khare
* Date             : 09/13/2017
* Compiler         : arm-none-eabi-gcc
* Linker           : arm-none-eabi-ld
* Debugger         : arm-none-eabi-gdb
* Reference        : IoT Lecture 3 slides on D2L
***************************************************************************************************/
//#include "main.h"
#include "em_cmu.h"

void cmu_init(void);
