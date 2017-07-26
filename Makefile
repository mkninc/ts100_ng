# Eingabebereich ******************************************************************
# Ausgabename der Hexdatei
OUTPUT_EXE=TS100_NG

# ---------------------------------------------------------------------------------
# Quelldateien , wichtig ist das "\" am Ende einer Zeile, wenn noch weitere Dateien
# folgen. Nach dem "\" dürfen keine weiteren Zeichen folgen.
SOURCE=$(APP_SOURCE_DIR)/startup.c \
		$(APP_SOURCE_DIR)/Analog.c \
		$(APP_SOURCE_DIR)/Bios.c \
		$(APP_SOURCE_DIR)/I2C.c \
		$(APP_SOURCE_DIR)/Interrupt.c \
		$(APP_SOURCE_DIR)/Main.c \
		$(APP_SOURCE_DIR)/MMA8652FC.c \
		$(APP_SOURCE_DIR)/Modes.c \
		$(APP_SOURCE_DIR)/Oled.c \
		$(APP_SOURCE_DIR)/PID.c \
		$(APP_SOURCE_DIR)/Settings.c \
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
		$(MCUAPI_DIR)/src/stm32f10x_wwdg.c
		

		
		
		
SOURCE_CPP=
#$(APP_SOURCE_DIR)/main.cpp \
#		$(APP_SOURCE_DIR)/clock_render.cpp \
#		$(APP_SOURCE_DIR)/neopixel.cpp \
#		$(APP_SOURCE_DIR)/RTCClock.cpp \
#		$(APP_SOURCE_DIR)/DCF77Clock.cpp \
#		$(APP_SOURCE_DIR)/TestClass.cpp
	
# ---------------------------------------------------------------------------------


# Verzeichnisse ----------------------------------------------------------------
GCC_DIR=H:/development/armgcc/6_2017-q2-update/bin
MCUAPI_DIR=StdPeriph_Driver
RTOS_DIR=FreeRTOS/Source

# Bibliotheken
DRV_LIB=$(MCUAPI_DIR)/driverlib
USB_LIB=$(MCUAPI_DIR)/usblib
DRV_LIB_LOCAL=DrvLib

# Verzeichnis der lokalen Quelldateien
APP_SOURCE_DIR=src
APP_INC_DIR=inc

# Verzeichnis fuer die Hexdateien
HEXFILE_DIR=Hexfile

# Verzeichnis fuer Objekt Dateien
OUTPUT_DIR=Objects

# Compiler Optimierungen -------------------------------------------------------
# no code optimization
OPTIM=-O0
#debug code optimization
#OPTIM=-Og
# size optimization
#OPTIM=-Os
# optimize code
#OPTIM=-O3

# Globale Definitionen
# Enable ROM library
#GLOBAL_DEFINES=-DTARGET_IS_BLIZZARD_RB1 -DUART_BUFFERED
# Without ROM library
#GLOBAL_DEFINES=-D DEPRECATED

# Enable debug code generation
DEBUG=-g
# Without debug code
#DEBUG=

BOOT_HEXFILE=backup/DFU_Flash_Backup.hex

# Ende Eingabebereich **********************************************************	
# Verwendete Bibliotheken ------------------------------------------------------
LIBS=

#$(DRV_LIB)/gcc/libdriver.a

# Linker script ----------------------------------------------------------------
LDSCRIPT_FLASH=LinkerScript2.ld
LDSCRIPT=$(LDSCRIPT_FLASH)
# ------------------------------------------------------------------------------
COMPILER=gcc
# Verwendete Programme ---------------------------------------------------------
CC=$(GCC_DIR)/arm-none-eabi-gcc
CPP=$(GCC_DIR)/arm-none-eabi-g++
AS=$(GCC_DIR)/arm-none-eabi-as
GCOV=$(GCC_DIR)/arm-none-eabi-gcov
OBJCOPY=$(GCC_DIR)/arm-none-eabi-objcopy
OBJDUMP=$(GCC_DIR)/arm-none-eabi-objdump
SIZE=$(GCC_DIR)/arm-none-eabi-size
SREC=srec_cat
SREC_INFO=srec_info

# Linker Optionen
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

# Allgemeine Compiler Optionen -------------------------------------------------
CPUFLAGS=-D GCC_ARMCM3		\
		-D ARM_MATH_CM3 	\
		-D STM32F10X_MD		\
		-D USE_STDPERIPH_DRIVER \
		-mthumb 			\
		-mcpu=cortex-m3 	\
		-mfpu=fpv4-sp-d16	\
		-mfloat-abi=soft
		
INCLUDES=-I$(APP_INC_DIR) \
		-I$(APP_SOURCE_DIR) \
		-I$(DRV_LIB) 		\
		-I$(MCUAPI_DIR) \
		-I$(RTOS_DIR)/include \
		-I$(RTOS_DIR)/portable/GCC/ARM_CM4F \
		-isystemStdPeriph_Driver/inc \
		-isystemCMSIS/device \
		-isystemCMSIS/core \

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
		-fno-rtti \
		-fno-exceptions \
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

# Regeln fuer die Erzeugung der Hex-Dateien 
# TODO: Bootloader groesse beim Aufruf von SREC
$(OUT_HEXFILE).hex : $(OUT_HEXFILE).srec
		@echo Erstelle $(OUT_HEXFILE).hex
		$(SREC_INFO) $(BOOT_HEXFILE) -Intel
		$(SREC_INFO) $(OUT_HEXFILE).hex -Intel
		@$(SREC) --line-length=43 $(OUT_HEXFILE).srec -motorola -O $(OUT_HEXFILE).hex -Intel
		$(SREC) --line-length=43 $(BOOT_HEXFILE) -Intel -crop 0x8000000 0x8004000 $(OUT_HEXFILE).srec -motorola -O $(OUT_HEXFILE)_FULL.hex -Intel
		$(SREC_INFO) $(OUT_HEXFILE)_FULL.hex -Intel
#		@$(SREC) --line-length=43 $(OUT_HEXFILE).bin -Binary -fill 0xFF 0x0000 0x1D000 -crop 0x1080 0x1CFFE -l-e-crc16 0x1CFFE -xmodem \
#								$(OUT_HEXFILE).bin -Binary -crop 0x0 0x1080 \
#								-O $(OUT_HEXFILE).hex -Intel
#		@$(SREC) --line-length=43 $(BOOT_BIN) -Binary -crop 0x0000 0x1000 \
#								 $(OUT_HEXFILE).hex -Intel -crop 0x1000 \
#								-O $(OUT_HEXFILE)_full.hex -Intel													
#		@$(SREC) --line-length=43 $(OUT_HEXFILE)_full.hex -Intel \
#								-O $(OUT_HEXFILE)_full.bin -Binary
#		@$(SREC) --line-length=43 -generate 0x1000 0x1004 -l-e-constant 0xFFFFFFFF 4 \
#								$(OUT_HEXFILE)_full.hex -Intel -crop 0x1004 0x1D000 \
#								-O $(OUT_HEXFILE)_update.hex -Intel
#		@$(OBJCOPY) $(OUT_HEXFILE)_full.bin -I binary -O elf32-littlearm $(OUT_HEXFILE)_full.axf

$(OUT_HEXFILE).axf : $(OUT_OBJS) $(OUT_OBJS_CPP) Makefile $(LDSCRIPT)
	@test -d $(@D) || mkdir -p $(@D)
	@echo Linking $(OUTPUT_EXE).axf  
	@$(CPP) $(CXXFLAGS) $(OUT_OBJS) $(OUT_OBJS_CPP) $(LIBS) $(LINKER_FLAGS)

$(OUT_OBJS): $(OUTPUT_DIR)/%.o : %.c Makefile
	@test -d $(@D) || mkdir -p $(@D)
	@echo Compiling ${<} 
	$(CC) -c $(CFLAGS) $< -o $@
	@$(OBJDUMP) -d -S $@ > $@.lst	 	
	
$(OUT_OBJS_CPP): $(OUTPUT_DIR)/%.o : %.cpp Makefile
	@test -d $(@D) || mkdir -p $(@D)
	@echo Compiling ${<} 
	$(CPP) -c $(CXXFLAGS) $< -o $@
	@$(OBJDUMP) -d -S $@ > $@.lst	 
			
clean :
	rm -Rf $(OUTPUT_DIR)
	rm -Rf $(HEXFILE_DIR)
	
# pull in dependency info for *existing* .o files
-include $(OUT_OBJS:.o=.d)
-include $(OUT_OBJS_CPP:.o=.d)
	
