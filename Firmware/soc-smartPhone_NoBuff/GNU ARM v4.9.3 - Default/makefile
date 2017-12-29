################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include protocol/bluetooth_2.6/lib/EFR32BG13P/EABI/subdir.mk
-include platform/middleware/glib/glib/subdir.mk
-include platform/middleware/glib/dmd/display/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/dmadrv/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32BG13P/Source/GCC/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include emlib/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: soc-smartPhone_NoBuff.axf

# Tool invocations
soc-smartPhone_NoBuff.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:\Users\Satyanarayana\SimplicityStudio\v4_workspace\soc-smartPhone_NoBuff\efr32bg13p632f512gm48.ld" -Xlinker -no-enum-size-warning -Xlinker -no-wchar-size-warning -Xlinker --gc-sections -Xlinker -Map="soc-smartPhone_NoBuff.map" -mfpu=fpv4-sp-d16 -mfloat-abi=hard -o soc-smartPhone_NoBuff.axf "./advertisement.o" "./app.o" "./app_hw.o" "./app_ui.o" "./application_properties.o" "./beacon.o" "./gatt_db.o" "./graphics.o" "./htm.o" "./ia.o" "./init_app.o" "./init_board.o" "./init_mcu.o" "./main.o" "./pti.o" "./emlib/em_adc.o" "./emlib/em_cmu.o" "./emlib/em_crypto.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_ldma.o" "./emlib/em_letimer.o" "./emlib/em_leuart.o" "./emlib/em_msc.o" "./emlib/em_rmu.o" "./emlib/em_rtcc.o" "./emlib/em_system.o" "./emlib/em_usart.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/bsp/bsp_stk_leds.o" "./hardware/kit/common/drivers/display.o" "./hardware/kit/common/drivers/displayls013b7dh03.o" "./hardware/kit/common/drivers/displaypalemlib.o" "./hardware/kit/common/drivers/i2cspm.o" "./hardware/kit/common/drivers/mx25flash_spi.o" "./hardware/kit/common/drivers/si7013.o" "./hardware/kit/common/drivers/tempsens.o" "./hardware/kit/common/drivers/udelay.o" "./platform/Device/SiliconLabs/EFR32BG13P/Source/GCC/startup_efr32bg13p.o" "./platform/emdrv/dmadrv/src/dmadrv.o" "./platform/emlib/src/em_cryotimer.o" "./platform/middleware/glib/dmd/display/dmd_display.o" "./platform/middleware/glib/glib/bmp.o" "./platform/middleware/glib/glib/glib.o" "./platform/middleware/glib/glib/glib_bitmap.o" "./platform/middleware/glib/glib/glib_circle.o" "./platform/middleware/glib/glib/glib_font_narrow_6x8.o" "./platform/middleware/glib/glib/glib_font_normal_8x8.o" "./platform/middleware/glib/glib/glib_font_number_16x20.o" "./platform/middleware/glib/glib/glib_line.o" "./platform/middleware/glib/glib/glib_polygon.o" "./platform/middleware/glib/glib/glib_rectangle.o" "./platform/middleware/glib/glib/glib_string.o" "./src/InitDevice.o" "./src/bma280.o" "./src/cmu.o" "./src/gpio.o" "./src/letimer0.o" "./src/spi.o" "C:\Users\Satyanarayana\SimplicityStudio\v4_workspace\soc-smartPhone_NoBuff\protocol\bluetooth_2.6\lib\EFR32BG13P\GCC\bgapi.a" "C:\Users\Satyanarayana\SimplicityStudio\v4_workspace\soc-smartPhone_NoBuff\protocol\bluetooth_2.6\lib\EFR32BG13P\EABI\binstack.o" "C:\Users\Satyanarayana\SimplicityStudio\v4_workspace\soc-smartPhone_NoBuff\protocol\bluetooth_2.6\lib\EFR32BG13P\EABI\stack.a" -lm -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: soc-smartPhone_NoBuff.hex'
	arm-none-eabi-objcopy -O ihex "soc-smartPhone_NoBuff.axf" "soc-smartPhone_NoBuff.hex"
	@echo ' '

	@echo 'Building bin file: soc-smartPhone_NoBuff.bin'
	arm-none-eabi-objcopy -O binary "soc-smartPhone_NoBuff.axf" "soc-smartPhone_NoBuff.bin"
	@echo ' '

	@echo 'Building s37 file: soc-smartPhone_NoBuff.s37'
	arm-none-eabi-objcopy -O srec "soc-smartPhone_NoBuff.axf" "soc-smartPhone_NoBuff.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "soc-smartPhone_NoBuff.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) soc-smartPhone_NoBuff.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
