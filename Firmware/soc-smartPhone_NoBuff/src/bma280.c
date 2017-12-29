/***********************************************************************************************//**
* File Name        : bma280.c
* File Description : This file contains the functions to set BMA280
* Compiler         : arm-none-eabi-gcc
* Linker           : arm-none-eabi-ld
* Debugger         : arm-none-eabi-gdb
*************************************************************************************************/
#include "spi.h"
#include "bma280.h"
#include "em_gpio.h"
#include "gpio.h"
#include "native_gecko.h"
#include "em_core.h"

/* BMA280 setup register macros */
#define PMU_RANGE_Reg 0x0F
#define PMU_BW_Reg 0x10
#define INT_8_Reg 0x2A
#define INT_9_Reg 0x2B
#define INT_EN_0_Reg 0x16
#define INT_MAP_0_Reg 0x19
#define INT_OUT_CTRL_Reg 0x20
#define INT_RST_LATCH_Reg 0x21
#define PMU_LPW_Reg 0x11
/* BMA280 setup register value macros */
#define PMU_RANGE_Val 0x05
#define PMU_BW_Val 0x0C
#define INT_8_Val 0x03
#define INT_9_Val 0x42
#define INT_EN_0_Val 0x10
#define INT_MAP_0_Val 0x10
#define INT_OUT_CTRL_Val 0x01
#define INT_RST_LATCH_Val 0x0C
#define SUSPEND 0x80
#define DISABLE_SUSPEND 0x00
/* TIMER0 TOP value macro for 1.8 ms delay */
#define TIMER_TOP_1_8_ms 22

//static void BMA_Soft_Reset(void)
//{
//	//CORE_DECLARE_IRQ_STATE;
////	BMA280_RegisterWrite(USART1,0x14,0xB6);
//	//CORE_ENTER_ATOMIC();
//	//gecko_sleep_for_ms(2);
//	//CORE_EXIT_ATOMIC();
//}
/**************************************************************************//**
 * @brief	SPI Read Register API accessing BMA280
 * @param	UsartNumber is the number of the USART to use (e.g. USART1)
 * @param	Address is the address of the register to read from
 * @return	Byte read
 *****************************************************************************/
uint8_t BMA280_RegisterRead(USART_TypeDef *usart, uint8_t address)
{
	usart->CMD |= USART_CMD_CLEARRX|USART_CMD_CLEARTX;
	uint16_t data;
	uint32_t tmp;
	data = 0x0080; //Byte order when sending is 0x80 0x00. MSB is set to indicate read for BMA280 chip
	data = data | address;  //Set address field
	/* Load data in TX buffer and transmit */
	while (!(usart->STATUS & USART_STATUS_TXBL));
	usart->TXDOUBLE = (uint32_t)data;
	while (!(usart->STATUS & USART_STATUS_TXC));
	/* Receive data from RX buffer */
	tmp = usart->RXDOUBLE;
	tmp = tmp >> 8;
	/* Return 8-bit data received */
	return (uint8_t)tmp;
}
/**************************************************************************//**
 * @brief	SPI Write Register API accessing BMA280
 * @param	UsartNumber is the number of the USART to use (e.g. USART1)
 * @param	Address is the address of the register to read from
 * @param	Data is one to be written
 * @return	None
 *****************************************************************************/
void BMA280_RegisterWrite(USART_TypeDef *usart, uint8_t address, uint8_t data)
{
	uint16_t tosend;
	uint32_t tmp;
	/* Combine data and address to send on the bus */
	tosend = (((uint16_t)data << 8) | (uint16_t)address);
	/* Load data in TX buffer and transmit */
	while (!(usart->STATUS & USART_STATUS_TXBL));
	usart->TXDOUBLE = (uint32_t)tosend;
	while (!(usart->STATUS & USART_STATUS_TXC));
	tmp = usart->RXDOUBLE;
	tmp = tmp >> 8;
}
/**************************************************************************//**
 * @brief	Enable SUSPEND mode for BMA280
 * @param	None
 * @return	None
 *****************************************************************************/
void BMA280_Normal_to_Suspend(void)
{
	/* Write to respective register to enable BMA280 in SUSPEND mode */
	//BMA280_RegisterWrite(USART1,PMU_LPW_Reg,SUSPEND);
}
/**************************************************************************//**
 * @brief	ENable NORMAL mode for BMA280
 * @param	None
 * @return	None
 *****************************************************************************/
void BMA280_Suspend_to_Normal(void)
{
//	//GPIO_PinOutSet(LED1_port, LED1_pin);	//if yes, set LED 1
//	/* Write to respective register to disable BMA280 in SUSPEND mode */
//	BMA280_RegisterWrite(USART1,PMU_LPW_Reg,DISABLE_SUSPEND);
//	/* Enable global interrupts */
//	BMA_Soft_Reset();
//	/* Initialize GPIO interrupt */
//	gpio_interrupt_int();
//	/* Start GPIO interrupt */
//	GPIO_IntEnable(GPIO_INT_ENABLE);
}
/**************************************************************************//**
 * @brief	Enable/Setup BMA280
 * @param	None
 * @return	None
 *****************************************************************************/
void BMA280_Enable(void)
{
	/* Set Range as +/-4g for BMA280 in PMU_RANGE register */
	/* Set Bandwidth as 125 Hz for BMA280 in PMU_BW register */
	/* Set Tap Quiet as 30 ms for BMA280 in INT_8 register */
	/* Set Tap Samples as 4 for BMA280 in INT_9 register */
	/* Set Tap Duration as 200 ms for BMA280 in INT_8 register */
	/* Set Tap Shock as 50 ms for BMA280 in INT_8 register */
	/* Set Tap Threshold as 250 mg for BMA280 in INT_9 register */

	BMA280_RegisterWrite(USART1,PMU_RANGE_Reg,PMU_RANGE_Val);
	BMA280_RegisterWrite(USART1,PMU_BW_Reg,PMU_BW_Val);
	BMA280_RegisterWrite(USART1,INT_8_Reg,INT_8_Val);
	BMA280_RegisterWrite(USART1,INT_9_Reg,INT_9_Val);
	BMA280_RegisterWrite(USART1,INT_EN_0_Reg,INT_EN_0_Val);
	BMA280_RegisterWrite(USART1,INT_MAP_0_Reg,INT_MAP_0_Val);
	BMA280_RegisterRead(USART1,INT_MAP_0_Reg);
	BMA280_RegisterWrite(USART1,INT_OUT_CTRL_Reg,INT_OUT_CTRL_Val);
	BMA280_RegisterWrite(USART1,INT_RST_LATCH_Reg,INT_RST_LATCH_Val);
}
