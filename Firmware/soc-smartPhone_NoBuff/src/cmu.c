/***********************************************************************************************//**
* File Name        : cmu.c
* File Description : This file contains the function to set up the clock for the MCU based on the
*                    energy modes
* Author           : Srishti Khare
* Date             : 09/13/2017
* Compiler         : arm-none-eabi-gcc
* Linker           : arm-none-eabi-ld
* Debugger         : arm-none-eabi-gdb
* Reference        : IoT Lecture 3 slides on D2L
***************************************************************************************************/
#include "cmu.h"
//#include "main.h"

volatile int mode;
/**************************************************************************//**
 * @brief	Initialize CMU
 * @param	None
 * @return	None
 *****************************************************************************/
void cmu_init(void){
	// Disable peripherals that the default initialization routine enables
	CMU_ClockEnable(cmuClock_GPCRC, true);
	CMU_ClockEnable(cmuClock_LDMA, true);
	CMU_ClockEnable(cmuClock_PRS, true);
	CMU_ClockEnable(cmuClock_RTCC, true);

	// By default, HFRCO is enabled  cmuHFRCOFreq_19M0Hz
	//CMU_HFRCOBandSet(cmuHFRCOFreq_19M0Hz); 				// Set HFRCO frequency

	//CMU_HFXOAutostartEnable(0, false, false);	//If false, HFXO is not started or selected automatically when enteringEM0/EM1
	//CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);	//Enable HFRCO
	//CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);	//Assign HFRCO to HF clock tree
	//CMU_OscillatorEnable(cmuOsc_HFXO, false, false);	//Disable HFXO

	//CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_TIMER0, true);
	//CMU_ClockEnable(cmuClock_LETIMER0, true);

	// FOR SPI
	//CMU_ClockSelectSet(cmuClock_HFPER, cmuSelect_HFRCO);
	//CMU_ClockEnable(cmuClock_HFPER, true);	// TIMER0
	CMU_ClockEnable(cmuClock_USART1, true);	//USART

	// FOR I2C
	CMU_ClockEnable(cmuClock_I2C0, true);

	CMU->ADCCTRL |= CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO;	//Set AUXHFRCO clock for ADC
	CMU_AUXHFRCOBandSet(cmuAUXHFRCOFreq_1M0Hz);	//Select 1 MHz clock
	CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, true);	// Enable AUXHFRCO
	CMU_ClockEnable(cmuClock_ADC0, true);	//Enable ADC clock

//	if(mode < 3)
//	{
		CMU_OscillatorEnable(cmuOsc_LFXO, true, true);	// Enable HFXO
		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);	// Select LFXO for clock tree LFA
		CMU_ClockDivSet(cmuClock_LETIMER0,cmuClkDiv_2);	// Divide clock by 2
//	}
//	else if(mode >= 3)
//	{
//		CMU_OscillatorEnable(cmuOsc_ULFRCO, true, true);	// Enable ULFRCO
//		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);	// Select ULFRCO for clock tree LFA
//		CMU_ClockDivSet(cmuClock_LETIMER0,cmuClkDiv_1);	// Divide clock by 1
//	}
	// Peripheral clocks enabled
	CMU_ClockEnable(cmuClock_GPIO, true);	//Enable GPIO clock
	CMU_ClockEnable(cmuClock_HFLE, true);	//Enable HFLE clock
	CMU_ClockEnable(cmuClock_LETIMER0, true);	//Enable LETIMER0 clock
}
