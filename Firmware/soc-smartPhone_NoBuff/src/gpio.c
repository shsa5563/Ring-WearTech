/***********************************************************************************************//**
* File Name        : gpio.c
* File Description : This file contains the function to set the GPIO pin connected to LED0, which is
*                    used for the Energy Modes assignment.
* Compiler         : arm-none-eabi-gcc
* Linker           : arm-none-eabi-ld
* Debugger         : arm-none-eabi-gdb
*************************************************************************************************/
#include "gpio.h"
//#include "main.h"
#include "em_gpio.h"
#include "bma280.h"
//#include "i2c.h"
#include "em_core.h"
#include "graphics.h"
#include "stdint.h"


//added shekhar
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* BG stack headers */
#include "bg_types.h"
#include "gatt_db.h"
#include "native_gecko.h"
#include "infrastructure.h"

/* application specific headers */
#include "app_hw.h"
#include "app_ui.h"
#include "app_timer.h"

/* Own header*/
#include "htm.h"
//end shekhar

/* Define single and double tap values */
#define SINGLETAP 0x20
#define DOUBLETAP 0x10

#define PMU_RANGE_Reg 0x0F
#define PMU_BW_Reg 0x10
#define PMU_RANGE_Val 0x05
#define PMU_BW_Val 0x0C
#define PMU_RANGE_Val1 0x03 //shekhar change to 2g
#define PMU_BW_Val1 0x0F // shekhar change to 2KHz

int switch_on = 0;
volatile int16_t xtempValue = 0;
volatile int16_t ytempValue = 0;
volatile int16_t ztempValue = 0;
volatile int16_t bma280_temp =0;
int16_t Xdata_FIFO;
int16_t Ydata_FIFO;
int16_t Zdata_FIFO;
static uint8_t fifo_index;
//bool i2c_flag = false;
/**************************************************************************//**
 * @brief	Initialize GPIO pins
 * @param	None
 * @return	None
 *****************************************************************************/
void gpio_init(void){

//	GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthStrongAlternateStrong);
//	GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull, LED0_default);
//
//	GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthStrongAlternateStrong);
//	GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, LED1_default);
//
//	GPIO_PinModeSet(ADC_port, ADC_pin, gpioModeDisabled, ADC_default);

	/*Over voltage disable for analog pin PortA pin 0*/
	//GPIO->P[gpioPortA].OVTDIS = 0x0001;

	GPIO_PinModeSet(SPI_CS_port, SPI_CS_pin, gpioModePushPull, SPI_CS_default);
	GPIO_PinModeSet(SPI_SCLK_port, SPI_SCLK_pin, gpioModePushPull, SPI_SCLK_default);
	GPIO_PinModeSet(SPI_MOSI_port, SPI_MOSI_pin, gpioModePushPull, SPI_MOSI_default);
	GPIO_PinModeSet(SPI_MISO_port, SPI_MISO_pin, gpioModeInput, SPI_MISO_default);

//	GPIO_PinModeSet(I2C_SCL_port, I2C_SCL_pin, gpioModeWiredAnd, I2C_SCL_default);
//	GPIO_PinModeSet(I2C_SDA_port, I2C_SDA_pin, gpioModeWiredAnd, I2C_SDA_default);
//	GPIO_PinModeSet(I2C_Bus_port, I2C_Bus_pin, gpioModePushPull, I2C_Bus_default);
}
/**************************************************************************//**
 * @brief	Initialize GPIO interrupt
 * @param	None
 * @return	None
 *****************************************************************************/
void gpio_interrupt_int(void)
{
	GPIO_IntClear(GPIO_IntGet());
	GPIO_PinModeSet(GPIO_INTERRUPT_port, GPIO_INTERRUPT_pin, gpioModeInput, GPIO_INTERRUPT_default);
	GPIO_IntConfig(GPIO_INTERRUPT_port, GPIO_INTERRUPT_pin, true, false, false);
	GPIO_IntEnable(GPIO_INT_ENABLE);
	//NVIC_SetPriority(GPIO_ODD_IRQn, 3);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
}
/**************************************************************************//**
 * @brief	GPIO Interrupt Handler
 * @param	None
 * @return	None
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
	CORE_ATOMIC_IRQ_DISABLE();
		//GPIO_PinOutClear(SPI_CS_port, SPI_CS_pin);
		//GPIO_PinModeSet(SPI_CS_port, SPI_CS_pin, gpioModePushPull, 0);
		BMA280_RegisterRead(USART1,0x16);
		BMA280_RegisterRead(USART1,0x16);
		//GPIO_PinOutClear(SPI_CS_port, SPI_CS_pin);
		BMA280_RegisterRead(USART1,0x21);

		bool flag = false;
		uint8_t rxdata = BMA280_RegisterRead(USART1,INT_STATUS_0);
		if((switch_on== 0) & (rxdata == 0x10))
		{
			//BMA280_RegisterWrite(USART1,0x16,0x20);
			//BMA280_RegisterWrite(USART1,0x19,0x20);

			GPIO_PinOutSet(LED0_port, LED0_pin);	//if yes, set LED 0
			switch_on++;
			/* BMA280_TEMP- SHEKHAR*/
						uint8_t temp_complement = BMA280_RegisterRead(USART1,0x08);
					    uint8_t sign = (temp_complement >> 7);
					    uint8_t temp = ~(temp_complement);
					    temp = temp + 1;
					    bma280_temp = (23 - temp);

					    xtempValue = 0;
					    ytempValue = 0;
					    ztempValue = 0;
					    BMA280_RegisterWrite(USART1,0x16,0x50);
					    			BMA280_RegisterWrite(USART1,0x19,0x50);

					    			GPIO_PinOutSet(LED0_port, LED0_pin);	//if yes, set LED 0

					    			BMA280_RegisterWrite(USART1,PMU_RANGE_Reg,PMU_RANGE_Val);
					    			BMA280_RegisterWrite(USART1,PMU_BW_Reg,PMU_BW_Val);

					    htmTemperatureMeasure();
			/* BMA280_TEMP- SHEKHAR*/

		}
//		else if((switch_on == 1) & (rxdata == 0x20))
//		{
//			BMA280_RegisterWrite(USART1,0x16,0x60);
//			BMA280_RegisterWrite(USART1,0x19,0x60);
//
//			GPIO_PinOutSet(LED0_port, LED0_pin);	//if yes, set LED 0
//
//			BMA280_RegisterWrite(USART1,PMU_RANGE_Reg,PMU_RANGE_Val);
//			BMA280_RegisterWrite(USART1,PMU_BW_Reg,PMU_BW_Val);
//
//		}
		else if(rxdata == 0x40)
		{
			uint8_t orient_data = BMA280_RegisterRead(USART1,0x0C);
			uint8_t Xdata_LSB = BMA280_RegisterRead(USART1,0x02);
			uint8_t Xdata_MSB = BMA280_RegisterRead(USART1,0x03);
			uint8_t Ydata_LSB = BMA280_RegisterRead(USART1,0x04);
			uint8_t Ydata_MSB = BMA280_RegisterRead(USART1,0x05);
			uint8_t Zdata_LSB = BMA280_RegisterRead(USART1,0x06);
			uint8_t Zdata_MSB = BMA280_RegisterRead(USART1,0x07);

			Xdata_FIFO= ((Xdata_MSB << 8) | Xdata_LSB );
			Ydata_FIFO= ((Ydata_MSB << 8) | Ydata_LSB );
			Zdata_FIFO= ((Zdata_MSB << 8) | Zdata_LSB );
		    fifo_index ++;
		    xtempValue = Xdata_FIFO;
		    ytempValue = Ydata_FIFO;
		    ztempValue = Zdata_FIFO;

			/* BMA280_TEMP- SHEKHAR*/
								uint8_t temp_complement = BMA280_RegisterRead(USART1,0x08);
							    uint8_t sign = (temp_complement >> 7);
							    uint8_t temp = ~(temp_complement);
							    temp = temp + 1;
							    bma280_temp = (23 - temp);
			/* BMA280_TEMP- SHEKHAR*/
	        htmTemperatureMeasure(); // shekhar: added this to send the data

			//BMA280_RegisterWrite(USART1,0x16,0x20);
			//BMA280_RegisterWrite(USART1,0x19,0x20);

		    GPIO_PinOutToggle(LED0_port, LED0_pin);
			switch_on = 0;
		}
		else if((rxdata == 0x10) & (switch_on == 0))
		{
			BMA280_RegisterWrite(USART1,0x16,0x10);
			BMA280_RegisterWrite(USART1,0x19,0x10);
			switch_on = 0;
	    	BMA280_RegisterWrite(USART1,PMU_RANGE_Reg,PMU_RANGE_Val);
	    	BMA280_RegisterWrite(USART1,PMU_BW_Reg,PMU_BW_Val);
		}
	//notification_flag = 2;
	//gecko_external_signal(0x00000001);
	GPIO_IntClear(GPIO_INT_ENABLE);   //Clear the interrupting flags
	GPIO_IntEnable(GPIO_INT_ENABLE);	//Enable GPIO Interrupts
	CORE_ATOMIC_IRQ_ENABLE();	//Enable global interrupts
}
