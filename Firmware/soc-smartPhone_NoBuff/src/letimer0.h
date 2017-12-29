/***********************************************************************************************//**
* File Name        : letimer.h
* File Description : This file contains the declaration of functions used to control the LETIMER
*                    routine of Blue Gecko
* Author           : Srishti Khare
* Date             : 09/13/2017
* Compiler         : arm-none-eabi-gcc
* Linker           : arm-none-eabi-ld
* Debugger         : arm-none-eabi-gdb
* * Reference      : IoT Lecture 4 slides on D2L
*************************************************************************************************/
#include "stdbool.h"
#include "gpio.h"
#include "em_letimer.h"

#ifndef SRC_LETIMER0_H_
#define SRC_LETIMER0_H_

	extern int comparator_0_value;
	extern void LETIMER0_IRQHandler(void);
	extern void LETIMER0_call(double comp_0_delay);
	extern bool i2c_flag;
//	extern double temperature_set_point;
//	extern float TEMP;
//	extern uint8_t ble_connection;

#endif /* SRC_LETIMER0_H_ */
