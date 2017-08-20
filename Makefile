OUTPUT_EXE=TS100_NG

# ------------------------------------------------------------------------------
SOURCE=$(APP_SOURCE_DIR)/startup.c \
		$(APP_SOURCE_DIR)/Analog.c \
		$(APP_SOURCE_DIR)/Bios.c \
		$(APP_SOURCE_DIR)/I2C.c \
		$(APP_SOURCE_DIR)/Interrupt.c \
		$(APP_SOURCE_DIR)/MMA8652FC.c \
		$(APP_SOURCE_DIR)/Oled.c \
		$(APP_SOURCE_DIR)/Settings.c \
		$(APP_SOURCE_DIR)/graphbuffer.c \
		$(MCUAPI_DIR)/src/misc.c \
		$(MCUAPI_DIR)/src/stm32f10x_adc.c \
		$(MCUAPI_DIR)/src/stm32f10x_bkp.c \
		$(MCUAPI_DIR)/src/stm32f10x_can.c \
		$(MCUAPI_DIR)/src/stm32f10x_cec.c \
		$(MCUAPI_DIR)/src/stm32f10x_crc.c \
		$(MCUAPI_DIR)/src/stm32f10x_dac.c \
		$(MCUAPI_DIR)/src/stm32f10x_dbgmcu.c \
		$(MCUAPI_DIR)/src/stm32f10x_dma.c \
		$(MCUAPI_DIR)/src/stm32f10x_exti.c \
		$(MCUAPI_DIR)/src/stm32f10x_flash.c \
		$(MCUAPI_DIR)/src/stm32f10x_fsmc.c \
		$(MCUAPI_DIR)/src/stm32f10x_gpio.c \
		$(MCUAPI_DIR)/src/stm32f10x_i2c.c \
		$(MCUAPI_DIR)/src/stm32f10x_iwdg.c \
		$(MCUAPI_DIR)/src/stm32f10x_pwr.c \
		$(MCUAPI_DIR)/src/stm32f10x_rcc.c \
		$(MCUAPI_DIR)/src/stm32f10x_rtc.c \
		$(MCUAPI_DIR)/src/stm32f10x_sdio.c \
		$(MCUAPI_DIR)/src/stm32f10x_spi.c \
		$(MCUAPI_DIR)/src/stm32f10x_tim.c \
		$(MCUAPI_DIR)/src/stm32f10x_usart.c \
		$(MCUAPI_DIR)/src/stm32f10x_wwdg.c \
		$(RTOS_DIR)/timers.c \
		$(RTOS_DIR)/tasks.c \
		$(RTOS_DIR)/queue.c \
		$(RTOS_DIR)/list.c \
		$(RTOS_DIR)/event_groups.c \
		$(RTOS_DIR)/croutine.c \
		$(RTOS_DIR)/portable/MemMang/heap_1.c \
		$(RTOS_DIR)/portable/GCC/ARM_CM3/port.c
		
		
		
SOURCE_CPP=$(APP_SOURCE_DIR)/Main.cpp \
		$(APP_SOURCE_DIR)/Modes.cpp \
		$(APP_SOURCE_DIR)/Heater.cpp \
		$(APP_SOURCE_DIR)/PID.cpp \
	
# ------------------------------------------------------------------------------

# path definitions -------------------------------------------------------------
MCUAPI_DIR=StdPeriph_Driver
RTOS_DIR=lib/FreeRTOS/Source

# lib path
DRV_LIB=$(MCUAPI_DIR)/driverlib
USB_LIB=$(MCUAPI_DIR)/usblib
DRV_LIB_LOCAL=DrvLib

# 
APP_SOURCE_DIR=src
APP_INC_DIR=inc

# output folder
HEXFILE_DIR=Hexfile

# temporary objects folder
OUTPUT_DIR=Objects

# code optimisation ------------------------------------------------------------
# no code optimization
#OPTIM=-O0
#debug code optimization
#OPTIM=-Og
# size optimization
OPTIM=-Os -finline-small-functions -findirect-inlining
# optimize code
#OPTIM=-O3

# global defines ---------------------------------------------------------------
# Enable ROM library
#GLOBAL_DEFINES=-DTARGET_IS_BLIZZARD_RB1 -DUART_BUFFERED
# Without ROM library
#GLOBAL_DEFINES=-D DEPRECATED
#GLOBAL_DEFINES += -D SIMULATION_BOARD
GLOBAL_DEFINES += -D USE_STDPERIPH_DRIVER 

# Enable debug code generation
DEBUG=-g
# Without debug code
#DEBUG=

BOOT_HEXFILE=backup/DFU_Flash_Backup.hex
	
# libs -------------------------------------------------------------------------
LIBS=

# linker script ----------------------------------------------------------------
LDSCRIPT=ts100_ng.ld

# ------------------------------------------------------------------------------
COMPILER=gcc
# programs ---------------------------------------------------------------------
CC=$(GCC_DIR)/arm-none-eabi-gcc
CPP=$(GCC_DIR)/arm-none-eabi-g++
AS=$(GCC_DIR)/arm-none-eabi-as
GCOV=$(GCC_DIR)/arm-none-eabi-gcov
OBJCOPY=$(GCC_DIR)/arm-none-eabi-objcopy
OBJDUMP=$(GCC_DIR)/arm-none-eabi-objdump
SIZE=$(GCC_DIR)/arm-none-eabi-size
SREC=srec_cat
SREC_INFO=srec_info

# linker flags -----------------------------------------------------------------
LINKER_FLAGS=-Wl,--gc-sections 		\
			-nostartfiles 		\
			-Xlinker 			\
			-o$(OUT_HEXFILE).axf 	\
			-Xlinker 			\
			-M 					\
			-Xlinker 			\
			-Map=$(OUT_HEXFILE).map \
			-lc \
			-lm 

# compiler flags ---------------------------------------------------------------
CPUFLAGS=-D GCC_ARMCM3		\
		-D ARM_MATH_CM3 	\
		-D STM32F10X_MD		\
		-mthumb 			\
		-mcpu=cortex-m3 	\
		-mfloat-abi=soft
		
INCLUDES=-I$(APP_INC_DIR) \
		-I$(APP_SOURCE_DIR) \
		-I$(MCUAPI_DIR) \
		-I$(RTOS_DIR)/include \
		-I$(RTOS_DIR)/portable/GCC/ARM_CM4F \
		-isystemStdPeriph_Driver/inc \
		-isystemCMSIS/device \
		-isystemCMSIS/core \
		-isystem$(RTOS_DIR)/include

CHECKOPTIONS=-pedantic 			\
			-Wall 				\
			-Wextra				\
			-Wunused			\
			-Wcomment 			\
			-Wtrigraphs			\
			-Wuninitialized		\
			-Wmissing-braces	\
			-Wfloat-equal		\
			-Wunreachable-code	\
			-Wswitch-default	\
			-Wreturn-type		\
			-Wundef				\
			-Wparentheses		\
			-Wnonnull			\
			-Winit-self			\
			-Wmissing-include-dirs	\
			-Wsequence-point	\
			-Wswitch			\
			-Wformat			\
			-Wsign-compare		\
			-Waddress			\
			-Waggregate-return	\
			-Wmissing-field-initializers	\
			-Winline			\
			-Wshadow			\
			-Wno-unused-parameter \
			-Wdouble-promotion  
			
CHECKOPTIONS_C=-Wmissing-prototypes \
			-Wimplicit			\
			-Wimplicit-function-declaration \
			-Wstrict-prototypes	\
			-Wdeclaration-after-statement	\
			-Wnested-externs	\
			-Wbad-function-cast
		
CXXFLAGS=$(CPUFLAGS) \
		$(DEBUG) 			\
		$(INCLUDES) \
		$(GLOBAL_DEFINES) 	\
		-D${COMPILER}  		\
		-MMD 				\
		$(CHECKOPTIONS)		\
		-std=c++17			\
		$(OPTIM) 			\
		-fno-common			\
		-ffreestanding		\
		-fno-rtti 			\
		-fno-exceptions 	\
		-fno-non-call-exceptions \
		-fno-use-cxa-atexit	\
		-T$(LDSCRIPT)	
		
		
CFLAGS=$(CPUFLAGS) \
		$(DEBUG) 			\
		$(INCLUDES) \
		$(CHECKOPTIONS_C) \
		$(GLOBAL_DEFINES) 	\
		-D${COMPILER}  		\
		-MMD 				\
		-std=c11			\
		$(OPTIM) 			\
		-fno-common			\
		-ffreestanding		\
		-T$(LDSCRIPT)

		
AFLAGS=$(CPUFLAGS) \
		$(DEBUG) 			\
		$(INCLUDES)

ifeq (${COMPILER}, gcc)
AFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -ffunction-sections -fdata-sections
endif

OBJS = $(SOURCE:.c=.o)
OBJS_CPP = $(SOURCE_CPP:.cpp=.o)

OUT_OBJS=$(addprefix $(OUTPUT_DIR)/,$(OBJS))
OUT_OBJS_CPP=$(addprefix $(OUTPUT_DIR)/,$(OBJS_CPP))
OUT_HEXFILE=$(addprefix $(HEXFILE_DIR)/,$(OUTPUT_EXE))
	 
all: $(OUT_HEXFILE).hex
	 
#
# The rule to create the target directory
#
$(OUT_HEXFILE).srec : $(OUT_HEXFILE).axf
		$(OBJCOPY) $(OUT_HEXFILE).axf -O srec $(OUT_HEXFILE).srec
		$(OBJDUMP) -d -S $(OUT_HEXFILE).axf > $(OUT_HEXFILE).lst
		$(SIZE) -x $(OUT_HEXFILE).axf

# Create hexfile
$(OUT_HEXFILE).hex : $(OUT_HEXFILE).srec
		@echo Create $(OUT_HEXFILE).hex
#		$(SREC_INFO) $(BOOT_HEXFILE) -Intel
		@$(SREC) --line-length=43 $(OUT_HEXFILE).srec -motorola -O $(OUT_HEXFILE).hex -Intel
		@$(SREC) --line-length=43 $(BOOT_HEXFILE) -Intel -crop 0x8000000 0x8004000 $(OUT_HEXFILE).srec -motorola -O $(OUT_HEXFILE)_FULL.hex -Intel
#		$(SREC_INFO) $(OUT_HEXFILE).hex -Intel
#		$(SREC_INFO) $(OUT_HEXFILE)_FULL.hex -Intel

$(OUT_HEXFILE).axf : $(OUT_OBJS) $(OUT_OBJS_CPP) Makefile $(LDSCRIPT)
	@test -d $(@D) || mkdir -p $(@D)
	@echo Linking $(OUTPUT_EXE).axf  
	@$(CPP) $(CXXFLAGS) $(OUT_OBJS) $(OUT_OBJS_CPP) $(LIBS) $(LINKER_FLAGS)

$(OUT_OBJS): $(OUTPUT_DIR)/%.o : %.c Makefile
	@test -d $(@D) || mkdir -p $(@D)
	@echo Compiling ${<} 
	@$(CC) -c $(CFLAGS) $< -o $@
	@$(OBJDUMP) -d -S $@ > $@.lst	 	
	
$(OUT_OBJS_CPP): $(OUTPUT_DIR)/%.o : %.cpp Makefile
	@test -d $(@D) || mkdir -p $(@D)
	@echo Compiling ${<} 
	@$(CPP) -c $(CXXFLAGS) $< -o $@
	@$(OBJDUMP) -d -S $@ > $@.lst	 
			
clean :
	rm -Rf $(OUTPUT_DIR)
	rm -Rf $(HEXFILE_DIR)
	
# pull in dependency info for *existing* .o files
-include $(OUT_OBJS:.o=.d)
-include $(OUT_OBJS_CPP:.o=.d)
	
