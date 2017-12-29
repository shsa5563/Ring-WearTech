/***********************************************************************************************//**
* File Name        : bma280.c
* File Description : This file contains the functions to set BMA280
* Compiler         : arm-none-eabi-gcc
* Linker           : arm-none-eabi-ld
* Debugger         : arm-none-eabi-gdb
*************************************************************************************************/
#ifndef SRC_BMA280_H_
#define SRC_BMA280_H_
	#define INT_STATUS_0 0x09
	//static void BMA_Soft_Reset(void);
	uint8_t BMA280_RegisterRead(USART_TypeDef *usart, uint8_t offset);
	void BMA280_RegisterWrite(USART_TypeDef *usart, uint8_t offset, uint8_t data);
	void BMA280_Normal_to_Suspend(void);
	void BMA280_Suspend_to_Normal(void);
	void BMA280_Enable(void);
#endif /* SRC_BMA280_H_ */
