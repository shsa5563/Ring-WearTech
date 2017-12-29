/***********************************************************************************************//**
* File Name        : gpio.h
* File Description : This file contains the GPIO pin configuration/mapping, which is connected to LED0 and is
*                    used for the Energy Modes assignment.
* Compiler         : arm-none-eabi-gcc
* Linker           : arm-none-eabi-ld
* Debugger         : arm-none-eabi-gdb
***************************************************************************************************/

//#include "main.h"
#include "em_gpio.h"

//extern bool i2c_flag;
//extern volatile int flag_pro_unpro;
//extern volatile int connection_flag;
extern volatile int notification_flag;
extern volatile int single_double;

// LED0 pin
#define	LED0_port	gpioPortF
#define LED0_pin	4
#define LED0_default	false 	// off
// LED1 pin
#define LED1_port	gpioPortF
#define LED1_pin	5
#define LED1_default	false	// off
// ADC pin
#define ADC_port	gpioPortA
#define ADC_pin	0
#define ADC_default	false	// off

/*// SPI_CS
#define SPI_CS_port	gpioPortA
#define SPI_CS_pin	3
#define SPI_CS_default	true	// on
// SPI_SCLK
#define SPI_SCLK_port	gpioPortA
#define SPI_SCLK_pin	2
#define SPI_SCLK_default	true	// on
// SPI_MOSI
#define SPI_MOSI_port	gpioPortA
#define SPI_MOSI_pin	0
#define SPI_MOSI_default	true	// on
// SPI_MISO
#define SPI_MISO_port	gpioPortA
#define SPI_MISO_pin	1
#define SPI_MISO_default	false	// off
// GPIO_INTERRUPT
#define GPIO_INTERRUPT_port	gpioPortD
#define GPIO_INTERRUPT_pin	14
#define GPIO_INTERRUPT_default	false	// off
// GPIO_POWER
#define GPIO_POWER_port	gpioPortD
#define GPIO_POWER_pin	15
#define GPIO_POWER_default	true	// off*/
// SPI_CS
#define SPI_CS_port	gpioPortC
#define SPI_CS_pin	9
#define SPI_CS_default	true	// on
// SPI_SCLK
#define SPI_SCLK_port	gpioPortC
#define SPI_SCLK_pin	8
#define SPI_SCLK_default	true	// on
// SPI_MOSI
#define SPI_MOSI_port	gpioPortC
#define SPI_MOSI_pin	6
#define SPI_MOSI_default	true	// on
// SPI_MISO
#define SPI_MISO_port	gpioPortC
#define SPI_MISO_pin	7
#define SPI_MISO_default	false	// off
// GPIO_INTERRUPT
#define GPIO_INTERRUPT_port	gpioPortD
#define GPIO_INTERRUPT_pin	11
#define GPIO_INTERRUPT_default	false	// off
// I2C_SCL
#define I2C_SCL_port	gpioPortC
#define I2C_SCL_pin	10
#define I2C_SCL_default	true	// off
// I2C_SDA
#define I2C_SDA_port	gpioPortC
#define I2C_SDA_pin	11
#define I2C_SDA_default	true	// off
// I2C_Bus
#define I2C_Bus_port	gpioPortD
#define I2C_Bus_pin	9
#define I2C_Bus_default	false	// off

#define GPIO_INT_ENABLE 0x00000800	//GPIO enable pin set value
/* GPIO related APIs declaration */
void gpio_init(void);
void GPIO_ODD_IRQHandler(void);
void gpio_interrupt_int(void);

