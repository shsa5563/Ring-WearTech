/***********************************************************************************************//**
 * \file   main.c
 * \brief  Silabs HTM IAS and Beaconing Demo Application
 *         This application is intended to be used with the iOS Silicon Labs
 *         app for demonstration purposes
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

#include "init_mcu.h"
#include "init_board.h"
#include "init_app.h"
#include "boards.h"
#include "ble-configuration.h"
#include "board_features.h"

/* BG stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"
#include "aat.h"

/* application specific files */
#include "app.h"

/* libraries containing default gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"

/* Device initialization header */
#include "hal-config.h"

/* BG stack headers */
#include "bg_types.h"
#include "native_gecko.h"

/* profiles */
#include "htm.h"
#include "ia.h"

/* BG stack headers*/
#include "gatt_db.h"

/* em library */
#include "em_system.h"

/* application specific headers */
#include "app_ui.h"
#include "app_hw.h"
#include "advertisement.h"
#include "beacon.h"
#include "app_timer.h"
#include "board_features.h"


#include "spi.h"
#include "bma280.h"


/* Own header */
#include "app.h"

#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif

#include "bsp.h"

#include "gpio.h"
#include "bma280.h"
#include "spi.h"
#include "letimer0.h"
#include "cmu.h"
#include "udelay.h"


#define INT_MAP_0_Reg 0x19
/***************************************************************************************************
 * Static Function Declarations
 **************************************************************************************************/
   #ifndef FEATURE_IOEXPANDER
/* Periodically called Display Polarity Inverter Function for the LCD.
   Toggles the the EXTCOMIN signal of the Sharp memory LCD panel, which prevents building up a DC
   bias according to the LCD's datasheet */
static void (*dispPolarityInvert)(void *);
  #endif /* FEATURE_IOEXPANDER */
/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app
 * @{
 **************************************************************************************************/

#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 4
#endif
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

// Gecko configuration parameters (see gecko_configuration.h)
static const gecko_configuration_t config = {
  .config_flags = 0,
  .sleep.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE,
  .bluetooth.max_connections = MAX_CONNECTIONS,
  .bluetooth.heap = bluetooth_stack_heap,
  .bluetooth.heap_size = sizeof(bluetooth_stack_heap),
  .bluetooth.sleep_clock_accuracy = 100, // ppm
  .gattdb = &bg_gattdb_data,
  .ota.flags = 0,
  .ota.device_name_len = 3,
  .ota.device_name_ptr = "OTA",
#if (HAL_PA_ENABLE) && defined(FEATURE_PA_HIGH_POWER)
  .pa.config_enable = 1, // Enable high power PA
  .pa.input = GECKO_RADIO_PA_INPUT_VBAT, // Configure PA input to VBAT
#endif // (HAL_PA_ENABLE) && defined(FEATURE_PA_HIGH_POWER)
};

/**
 * button initialization. Configure pushbuttons PB0,PB1
 * as inputs.
 */
static void button_init()
{
	// Configure pin as input
	  GPIO_PinModeSet(BSP_BUTTON0_PORT, BSP_BUTTON0_PIN, gpioModeInput, 1);
	  // Configure pin as input
	  GPIO_PinModeSet(BSP_BUTTON1_PORT, BSP_BUTTON1_PIN, gpioModeInput, 1);
}

/**
 * LED initialization. Configure LED pins as outputs
 */
static void led_init()
{
  // configure LED0 and LED1 as outputs
  GPIO_PinModeSet(BSP_LED0_PORT, BSP_LED0_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(BSP_LED0_PORT, BSP_LED0_PIN, gpioModePushPull, 0);
}

/**************************************************************************//**
 * @brief   Register a callback function at the given frequency.
 *
 * @param[in] pFunction  Pointer to function that should be called at the
 *                       given frequency.
 * @param[in] argument   Argument to be given to the function.
 * @param[in] frequency  Frequency at which to call function at.
 *
 * @return  0 for successful or
 *         -1 if the requested frequency does not match the RTC frequency.
 *****************************************************************************/
int rtcIntCallbackRegister(void (*pFunction)(void*),
                           void* argument,
                           unsigned int frequency)
{
  #ifndef FEATURE_IOEXPANDER

  dispPolarityInvert =  pFunction;
  /* Start timer with required frequency */
  gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(1000 / frequency), DISP_POL_INV_TIMER, false);

  #endif /* FEATURE_IOEXPANDER */

  return 0;
}

void main(void)
{
//  // Initialize device
//  initMcu();
//  // Initialize board
//  initBoard();
//  // Initialize application
//  initApp();
//
//  // Initialize LEDs
//  BSP_LedsInit();
//
//#ifndef FEATURE_LED_BUTTON_ON_SAME_PIN
//  // Configure pin as input
//  GPIO_PinModeSet(BSP_BUTTON0_PORT, BSP_BUTTON0_PIN, gpioModeInput, 1);
//  // Configure pin as input
//  GPIO_PinModeSet(BSP_BUTTON1_PORT, BSP_BUTTON1_PIN, gpioModeInput, 1);
//#endif

#ifdef FEATURE_SPI_FLASH
	  /* Put the SPI flash into Deep Power Down mode for those radio boards where it is available */
	  MX25_init();
	  MX25_DP();
	  /* We must disable SPI communication */
	  USART_Reset(USART1);

	#endif /* FEATURE_SPI_FLASH */

	  /* Initialize peripherals */
	  enter_DefaultMode_from_RESET();

  // Initialize stack
  gecko_init(&config);

  /* Initialize clocks */
   cmu_init();

   gpio_init();

   LETIMER0_call(2);

   /* Initialize SPI */
   spi_init();

   /* Enable BMA280 in SUSPEND mode */
 //  BMA280_Enable();
      led_init();
     button_init();

     //LCD_init();

   /* Initialize GPIO interrupt */
   gpio_interrupt_int();

   /* Start GPIO interrupt */
   GPIO_IntEnable(GPIO_INT_ENABLE);

   BMA280_Enable();

  while (1) {
	//BMA280_Enable();
    struct gecko_cmd_packet* evt;
    // Check for stack event.
    evt = gecko_wait_event();
    // Run application and event handler.
    /* Flag for indicating DFU Reset must be performed */
      static uint8_t boot_to_dfu = 0;
      //BMA280_RegisterRead(USART1,INT_MAP_0_Reg);

      switch (BGLIB_MSG_ID(evt->header)) {
        /* Boot event and connection closed event */
        case gecko_evt_system_boot_id:
        case gecko_evt_le_connection_closed_id:

          /* Initialize app */
          appInit(); /* App initialization */
         // BMA280_RegisterRead(USART1,INT_MAP_0_Reg);
          htmInit(); /* Health thermometer initialization */
          //BMA280_RegisterRead(USART1,INT_MAP_0_Reg);
          advSetup(); /* Advertisement initialization */
          //BMA280_RegisterRead(USART1,INT_MAP_0_Reg);

          /* Enter to DFU OTA mode if needed */
          if (boot_to_dfu) {
            gecko_cmd_system_reset(2);
          }

          break;

        /* Connection opened event */
        case gecko_evt_le_connection_opened_id:
          /* Call advertisement.c connection started callback */
          advConnectionStarted();
          //BMA280_RegisterRead(USART1,INT_MAP_0_Reg);
          break;

        /* Value of attribute changed from the local database by remote GATT client */
        case gecko_evt_gatt_server_attribute_value_id:
          /* Check if changed characteristic is the Immediate Alert level */
          if ( gattdb_alert_level == evt->data.evt_gatt_server_attribute_value.attribute) {
            /* Write the Immediate Alert level value */
            iaImmediateAlertWrite(&evt->data.evt_gatt_server_attribute_value.value);
            //BMA280_RegisterRead(USART1,INT_MAP_0_Reg);
          }
          break;

        /* Indicates the changed value of CCC or received characteristic confirmation */
        case gecko_evt_gatt_server_characteristic_status_id:
          /* Check if changed client char config is for the temperature measurement */
          if ((gattdb_temp_measurement == evt->data.evt_gatt_server_attribute_value.attribute)
              && (evt->data.evt_gatt_server_characteristic_status.status_flags == 0x01)) {
            /* Call HTM temperature characteristic status changed callback */
            htmTemperatureCharStatusChange(
              evt->data.evt_gatt_server_characteristic_status.connection,
              evt->data.evt_gatt_server_characteristic_status.client_config_flags);
          }
          break;

        /* Software Timer event */
        case gecko_evt_hardware_soft_timer_id:
          /* Check which software timer handle is in question */

          switch (evt->data.evt_hardware_soft_timer.handle) {
            case UI_TIMER: /* App UI Timer (LEDs, Buttons) */
              appUiTick();
              break;
            case ADV_TIMER: /* Advertisement Timer */
              advSetup();
              break;
            case TEMP_TIMER: /* Temperature measurement timer */
              /* Make a temperature measurement */
              htmTemperatureMeasure();
              break;
//            #ifndef FEATURE_IOEXPANDER
//            case DISP_POL_INV_TIMER:
//              /*Toggle the the EXTCOMIN signal, which prevents building up a DC bias  within the
//               * Sharp memory LCD panel */
//              dispPolarityInvert(0);
//              break;
//            #endif /* FEATURE_IOEXPANDER */
            default:
              break;
          }
          break;

        /* User write request event. Checks if the user-type OTA Control Characteristic was written.
         * If written, boots the device into Device Firmware Upgrade (DFU) mode. */
        case gecko_evt_gatt_server_user_write_request_id:
          /* Handle OTA */
          if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
            /* Set flag to enter to OTA mode */
            boot_to_dfu = 1;
            /* Send response to Write Request */
            gecko_cmd_gatt_server_send_user_write_response(
              evt->data.evt_gatt_server_user_write_request.connection,
              gattdb_ota_control,
              bg_err_success);

            /* Close connection to enter to DFU OTA mode */
            gecko_cmd_endpoint_close(evt->data.evt_gatt_server_user_write_request.connection);
          }
          break;

        default:
        	//BMA280_RegisterRead(USART1,INT_MAP_0_Reg);
          break;
      }
   // appHandleEvents(evt);
    //BMA280_Enable();
  }
}

/** @} (end addtogroup app) */
/** @} (end addtogroup Application) */
