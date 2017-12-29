/***********************************************************************************************//**
* File Name        : sleep.c
* File Description : This file contains the function to set the GPIO pin connected to LED0, which is
*                    used for the Energy Modes assignment.
* Author           : Srishti Khare
* Date             : 09/13/2017
* Compiler         : arm-none-eabi-gcc
* Linker           : arm-none-eabi-ld
* Debugger         : arm-none-eabi-gdb
* Reference        : IoT Lecture 4 slides on D2L
***************************************************************************************************/
#include "letimer0.h"
#include "native_gecko.h"
#include "gatt_db.h"
#include "em_core.h"
#include "em_letimer.h"
#include "bma280.h"

#define MODE_0_1_2_CLOCK 16384
#define MODE_3_CLOCK 1000
#define SINGLETAP 0x20
#define DOUBLETAP 0x10

volatile int mode1 = 0;	//declaration of variable to store energy node information
//void blockSleepMode(sleepstate_enum minimumMode);	//declaration of blockSleepMode function
/**************************************************************************//**
 * @brief	LETIMER0 Interrupt Handler
 * @param	None
 * @return	None
 *****************************************************************************/
void LETIMER0_IRQHandler(void)
{
   int intFlags;	//Variable to store the interrupting flags
   CORE_ATOMIC_IRQ_DISABLE();	//Disable interrupts to avoid nesting
   intFlags = LETIMER_IntGet(LETIMER0);    //Get the interrupting flags
   LETIMER_IntClear(LETIMER0, intFlags);   //Clear the interrupting flags

   if(intFlags & LETIMER_IF_COMP0)	//checks if COMP0 flag is set and I2C is enabled
   {
	 //  notification_flag = 1;
	   gecko_external_signal(0x00000001);
   }
   CORE_ATOMIC_IRQ_ENABLE();	//Re-enable interrupts
}
/**************************************************************************//**
 * @brief	Initialize and start LETIMER0
 * @param	Comparator 1 value
 * @param	Comparator 2 value
 * @return	None
 *****************************************************************************/
void LETIMER0_call(double comp_0_delay)
{
	int comparator_0_value=0;	//initialize comparator value variables

	const LETIMER_Init_TypeDef letimerInit =
		{
		    .enable         = false,                 //Start counting when init completed
			.debugRun       = false,                 //Counter shall not keep running during debug halt
			//.rtcComp0Enable = false,                //Don't start counting on RTC COMP0 match
			//.rtcComp1Enable = false,                //Don't start counting on RTC COMP1 match
			.comp0Top       = true,                 //Load COMP0 register into CNT when counter underflows. COMP0 is used as TOP
			.bufTop         = false,                //Don't load COMP1 into COMP0 when REP0 reaches 0
			.out0Pol        = 0,                    //Idle value for output 0.
			.out1Pol        = 0,                    //Idle value for output 1.
			.ufoa0          = letimerUFOANone,      //PWM output on output 0
			.ufoa1          = letimerUFOANone,      //Pulse output on output 1
			.repMode        = letimerRepeatFree     //Count until stopped
		};

		LETIMER_Init(LETIMER0, &letimerInit);	//initializes LETIMER

//		if(mode1 < 3)	//if modes EM0, EM1 or EM2 are selected (clock has 32768 ticks/second)
//		{
	        comparator_0_value = (int)(MODE_0_1_2_CLOCK*comp_0_delay);	//set comparator0 value
//		}
//		else	//if modes EM3 or EM4 are selected (clock has 1000 ticks/second)
//		{
//			comparator_0_value = (int)(MODE_3_CLOCK*comp_0_delay);	//set comparator0 value
//		}

		LETIMER_CompareSet(LETIMER0, 0, comparator_0_value);	//load the comparator value

		LETIMER_IntClear(LETIMER0, LETIMER_IFC_UF | LETIMER_IFC_COMP0);	//clear LETIMER interrupt
		LETIMER_IntEnable(LETIMER0 , LETIMER_IEN_COMP0);	//enable LETIMER interrupt

		NVIC_EnableIRQ(LETIMER0_IRQn);	//enable external interrupt
		LETIMER0->CMD = LETIMER_CMD_START;	//start LETIMER0
}
