## For Windows users :
## 1. Install Cygwin environment then add to you system PATH.
## Necessary Cygwin packages : 
##					make , ctags 
## 2. Install GNU arm-none-eabi toolchain, add it to your system PATH.

###################### Project Final Executable Name ########################
TARGET := bare_test
#############################################################################

BUILD_DIR := build

###################### MS-Dos Style ToolChain PATH ##########################
TOOLCHAIN_PATH = "C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10"
#############################################################################

######################     ToolChain Version       ##########################
## '' braces are Cygwin environment mandatory 
TOOLCHAIN_VER = '10 2021.10'
#############################################################################

###################### Standard Peripheral Library path #####################
STD_PERIPH_DIR = ./STM32F10x_StdPeriph_Lib_V3.6.0
#############################################################################

###################### If enabling semihosting features #####################
SEMIHOST = 0
#############################################################################

######################  If enabling segger-rtt support  #####################
USE_SEGGER_RTT = 0
#############################################################################

######################  If enabling SGL support  ############################
USE_SGL = 1
#############################################################################

######################  Debugger Config #####################################
## 0 for STLink V2 , 1 for Segger J-Link
DEBUGGER = 1
#############################################################################

###################### Project-wise Macro Definitions #######################
MACROS = -D 'assert_param(expr)=((void)0)' \
		 -D STM32F10X_HD \
		 -D DBG_LEVEL=0 \
		 -D DEBUG \
		 -D USE_STDPERIPH_DRIVER \
		 -D NDEBUG

ifeq ($(USE_SEGGER_RTT),1)
MACROS += -D USE_SEGGER_RTT
endif

ifeq ($(USE_SGL),1)
MACROS += -D USE_SGL
endif

#############################################################################

ARCH_CFG = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft 

# -march=armv7-m : ARM Cortex-M3 architecture
# -mthumb : generate thumb instructions
# -Wall : enable all warnings
# -Os : optimize for size
# -std=gnu11 : use GNU C11 standard
# -g : generate debugging information
CCFLAGS = $(ARCH_CFG) -Wall -O3 -std=c99 -g3 $(INCLUDES) $(MACROS)
LDFLAGS =  -Tstm32f1x_64KB_flash.ld 
#LDFLAGS += -nostdlib
#LDFLAGS += -static
LDFLAGS += -specs=nosys.specs
LDFLAGS += -mcpu=cortex-m3
#LDFLAGS += -mfloat-abi=soft -mthumb
#LDFLAGS += -specs=nano.specs
#LDFLAGS += -Wl,--start-group
#LDFLAGS += -lc
LDFLAGS += -lm 
#LDFLAGS += -Wl,--end-group

ifeq ($(USE_CYGWIN),1)
#Test if linking to the wrong libs under windows orther wise just delete this path spec.
#LIB_PATH += -L$(CYGWIN_TOOLCHAIN_PREFIX)/$(TOOLCHAIN_VER)/arm-none-eabi/lib/
endif

# Creating the map file
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

### Optmization for ELF size heavily
LDFLAGS += -Wl,--gc-sections
CCFLAGS += -ffunction-sections -fdata-sections

### Suppresing compiler warnings ###
CCFLAGS += -Wno-strict-aliasing
CCFLAGS += -Wno-maybe-uninitialized
CCFLAGS += -Wno-missing-braces
CCFLAGS += 



ifeq ($(SEMIHOST),1)
CCFLAGS += --specs=rdimon.specs
LDFLAGS := $(filter-out -nostdlib,$(LDFLAGS))
LDFLAGS += -lc -lrdimon
LIB_PATH += -L$(CYGWIN_TOOLCHAIN_PREFIX)/$(TOOLCHAIN_VER)/arm-none-eabi/lib/
endif


INCLUDES = \
			-I$(STD_PERIPH_DIR)/Libraries/CMSIS/CM3/CoreSupport \
			-I$(STD_PERIPH_DIR)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x \
			-I$(STD_PERIPH_DIR)/Libraries/STM32F10x_StdPeriph_Driver/inc \
			-ISEGGER_RTT \
			-IAPPLICATION \
			-IAPPLICATION/sgl \
			-IDRIVERS \
			-ISYSTEM \
			-I. \
			
ifeq ($(USE_SGL),1)
	INCLUDES += -I$(SGL_DIR) \
				-I$(SGL_DIR)/core \
				-I$(SGL_DIR)/draw \
				-I$(SGL_DIR)/fonts \
				-I$(SGL_DIR)/widget \
				-I$(SGL_DIR)/stdlib \
				-I$(SGL_DIR)/stdlib/heap \
				
endif


STD_PERIPH_LIB_SOURCES = \
			$(wildcard $(STD_PERIPH_DIR)/Libraries/CMSIS/CM3/CoreSupport/*.c) \
			$(wildcard $(STD_PERIPH_DIR)/Libraries/STM32F10x_StdPeriph_Driver/src/*.c)  

SOURCES =  \
            $(wildcard ./*.c)  \
            $(wildcard ./3rd-party/*.c)  \
            $(wildcard ./application/*.c)  \
			
SOURCES +=  $(wildcard ./drivers/*.c) \
            $(wildcard ./system/*.c)  


ASM_SOURCES =	$(wildcard ./*.s)

######################################
# SGL sources
######################################
SGL_DIR = ./sgl/source
ifeq ($(USE_SGL),1)
SGL_SOURCES = $(wildcard $(SGL_DIR)/*.c)  \
			  $(wildcard $(SGL_DIR)/core/*.c)  \
			  $(wildcard $(SGL_DIR)/draw/*.c)  \
			  $(wildcard $(SGL_DIR)/fonts/*.c)  \
			  $(wildcard $(SGL_DIR)/widget/*.c)  \

SGL_SOURCES += $(wildcard $(SGL_DIR)/stdlib/*.c)
SGL_SOURCES += $(wildcard $(SGL_DIR)/stdlib/heap/*.c)
SGL_SOURCES += $(wildcard ./application/sgl/*.c)

endif


ifeq ($(USE_SEGGER_RTT),1)
SOURCES +=  $(wildcard ./SEGGER_RTT/*.c)  
endif


# Prerequisits file looking up path for GNU make
vpath %.c $(sort $(dir $(SOURCES))) 
vpath %.c $(sort $(dir $(STD_PERIPH_LIB_SOURCES)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

ifeq ($(USE_SGL),1)	 
vpath %.c $(sort $(dir $(SGL_SOURCES)))
endif


### Toolchain Settings ###

PREFIX = $(CYGWIN_TOOLCHAIN_PREFIX)/$(TOOLCHAIN_VER)/bin/arm-none-eabi-
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
OD = $(PREFIX)objdump
GDB = $(PREFIX)gdb
HEX =$(CP) -O ihex
BIN =$(CP) -O binary -S
STRIP =$(PREFIX)strip	# Omit all symbol information from the ouput file


### OS dependence Variables Settings ###

ifeq ($(OS),Windows_NT) 
# For MS-Dos platform.
$(info Windows environment detected. os:$(OS))

ifneq ("",$(findstring /bin/sh,$(SHELL)))
$(info Cygwin  environment detected. shell:$(SHELL))
	RM = rm -f
	USE_CYGWIN = 1
	START = sh -c
	ECHO := echo -e
else 
$(error Cygwin not found, abort. shell:$(SHELL))
	RM = del /Q /S
endif

endif

UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
# For Darwin platform.
		RM = rm -rf
		ECHO := echo

		DIR_PREFIX = /Users/moses/Downloads
#		STD_PERIPH_DIR := $(shell ls -d $(DIR_PREFIX)/STM32F10x_StdPeriph_Lib_V3.6.?)
		OPENOCD_PREFIX = $(DIR_PREFIX)/xpack-openocd-0.12.?-?
		GNU_PREFIX = $(DIR_PREFIX)/gcc-arm-none-eabi-10.?-202?.??/bin

		CC := $(GNU_PREFIX)/arm-none-eabi-gcc
		OBJDUMP := $(GNU_PREFIX)/arm-none-eabi-objdump
		SZ = $(GNU_PREFIX)/arm-none-eabi-size


		MSG_SUPRESS = > ./server.log 2>&1 
		GDB_CMD = $(GNU_PREFIX)/arm-none-eabi-gdb-py
		OPENOCD = $(OPENOCD_PREFIX)/bin/openocd
		CHIP_CFG = $(OPENOCD_PREFIX)/openocd/scripts/target/stm32f1x.cfg 


		ifeq ($(DEBUGGER),0)
		DEBUGGER_CFG = $(OPENOCD_PREFIX)/openocd/scripts/interface/stlink.cfg
		else 
		DEBUGGER_CFG = $(OPENOCD_PREFIX)/openocd/scripts/interface/jlink.cfg
		endif

endif
ifeq ($(UNAME),Linux)
# For Linux platform.
		RM = rm -rvf

		MSG_SUPRESS = > ./server.log 2>&1 
		GDB_CMD = arm-none-eabi-gdb-py
		OPENOCD = openocd
		STLINK_CFG = /usr/local/share/openocd/scripts/interface/stlink.cfg
		CHIP_CFG = /usr/local/share/openocd/scripts/target/stm32f1x.cfg 
	
		STD_PERIPH_DIR = /home/moses/code/STM32F10x_StdPeriph_Lib_V3.6.0 

endif	

# 3rd-party : StdPeriph Library Object files
STD_PERIPH_BUILD_DIR = $(BUILD_DIR)/STM32F10x_StdPeriph_Lib_V3.6.0/
STD_PERIPH_LIB_OBJECTS = $(addprefix $(STD_PERIPH_BUILD_DIR)/,$(notdir $(STD_PERIPH_LIB_SOURCES:.c=.o)))

# 3rd-party : SGL Library Object files
SGL_BUILD_DIR = $(BUILD_DIR)/SGL/
SGL_LIB_OBJECTS = $(addprefix $(SGL_BUILD_DIR)/,$(notdir $(SGL_SOURCES:.c=.o)))

# Porject-wise Object files
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))

PREPROCS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:.c=.I)))
PREPROCS += $(addprefix $(STD_PERIPH_BUILD_DIR)/,$(notdir $(STD_PERIPH_LIB_SOURCES:.c=.I)))


all : $(TARGET).elf 


# Linking Object Files
$(TARGET).elf: $(STD_PERIPH_LIB_OBJECTS) $(OBJECTS) $(SGL_LIB_OBJECTS)  
	@$(ECHO) "LD $@"
	@$(CC) $^ $(LDFLAGS) -o $@ 
	@$(ECHO) "SIZE $@"
	@$(SZ)  $@
#	@$(STRIP) $@


# Building the Project Library Object files.
 $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	@$(ECHO) "CC $<"
	@$(CC) -c $(CCFLAGS) \
		 $< -o $@

 $(BUILD_DIR)/%.o: %.s
	@mkdir -p $(BUILD_DIR)
	@$(ECHO) "AS $<"
	@$(CC) -c $(CCFLAGS) \
		 $< -o $@

# Building the Project Library preprocessor output files.
 $(BUILD_DIR)/%.I: %.c
	@mkdir -p $(BUILD_DIR)
	@$(ECHO) "CC -E $@"
	@$(CC) -E $(CCFLAGS) \
		 $< -o $@

# Building the StdPeriph Library Object files.
$(STD_PERIPH_BUILD_DIR)/%.o: %.c
	@mkdir -p $(STD_PERIPH_BUILD_DIR)
	@$(ECHO) "CC $<"
	@$(CC) -c $(CCFLAGS) \
		 $< -o $@

# Building the StdPeriph preprocessor Object files.
$(STD_PERIPH_BUILD_DIR)/%.I: %.c
	@mkdir -p $(STD_PERIPH_BUILD_DIR)
	@$(ECHO) "CC -E $@"
	@$(CC) -E $(CCFLAGS) \
		 $< -o $@

# Building the SGL Library Object files.
$(SGL_BUILD_DIR)/%.o: %.c
	@mkdir -p $(SGL_BUILD_DIR)
	@$(ECHO) "CC $<"
	@$(CC) -c $(CCFLAGS) \
		 $< -o $@

preproc : $(PREPROCS)


strip : $(TARGET).elf
	@$(call COL,$(YELLOW), STRIP $<)
	@$(STRIP) $<

strip_size : $(TARGET).elf strip
	@$(call COL,$(YELLOW), SIZE $<)
	@$(SZ) $<

size : $(TARGET).elf 
	@$(call COL,$(YELLOW), SIZE $<)
	@$(SZ) $<


# Updating ctags for the project.
tags : clean_tags
	@$(call COL,$(GREEN),Generating new tags ...)
	@ctags -R -a ./*
	@$(call COL,$(LIGHT_GREEN),Finished.)


# Only clean project related files, keep sub-folders/3-rdparty lib content.
clean :
	@$(call COL,$(GREEN),Cleaning output files)
	@$(RM)  *.o *_debug *_disa *_bin *_layout *.elf *.map *.swp *.log 
	@$(RM) $(BUILD_DIR)/*.o $(BUILD_DIR)/*.map
	@$(call COL,$(LIGHT_GREEN),Finished.)

# Only clean sgl build output files.
clean_sgl :
	@$(call COL,$(GREEN),Cleaning SGL build files)
	@$(RM) -r $(SGL_BUILD_DIR)/*
	@$(call COL,$(LIGHT_GREEN),Finished.)


clean_tags : 
	@$(call COL,$(GREEN),Cleaning generated tags)
	@$(RM) tags

clean_all : 
	@$(call COL,$(GREEN),Cleaning all build files)
	@$(RM) -r $(BUILD_DIR)
	@$(call COL,$(LIGHT_GREEN),Finished.)



# function COL : Generating color formatted output.
#Usage :	@$(call COL,$(color),output messages)
define COL
	$(eval $@_COLOR_START = $(1))
	$(eval $@_CONTENT = $(2))
	$(eval $@_COLOR_END = $(NC))
	$(ECHO) "${$@_COLOR_START}${$@_CONTENT}"${$@_COLOR_END}
endef
	
# Ouput color tables 
BLACK  :=  \033[0;30m
RED    :=  \033[0;31m
GREEN  :=  \033[0;32m
BROWN  :=  \033[0;33m
BLUE   :=  \033[0;34m
PURPLE :=  \033[0;35m
CYAN   :=  \033[0;36m

LIGHT_GRAY     :=  \033[0;37m
DARK_GRAY      :=  \033[1;30m
LIGHT_RED      :=  \033[1;31m
LIGHT_GREEN    :=  \033[1;32m
YELLOW		   :=  \033[1;33m
LIGHT_BLUE     :=  \033[1;34m
LIGHT_PURPLE   :=  \033[1;35m
LIGHT_CYAN     :=  \033[1;36m
WHITE		   :=  \033[1;37m

NC     :=  '\033[0m'

 
##############################################################################################################
########################   OPENOCD SERVER AND GDB DEBUGGING COMMAND WRAPPERS  ################################
##############################################################################################################
########################   OpenOCD Cygwin file PATH Configurations            ################################
ifeq ($(USE_CYGWIN), 1)
CYGWIN_TOOLCHAIN_PREFIX = /cygdrive/c/'Program Files (x86)'/'GNU Arm Embedded Toolchain'
OPENOCD_PREFIX = $(CYGWIN_TOOLCHAIN_PREFIX)/xpack-openocd-0.12.0-2/
OPENOCD = $(OPENOCD_PREFIX)/bin/openocd.exe
#CHIP_CFG = "C:\Program Files (x86)\GNU Arm Embedded Toolchain\xpack-openocd-0.12.0-2\openocd\scripts\target\stm32f1x.cfg"
CHIP_CFG = ".\device\stm32f103RC.cfg"		## Project-wise modified alternative.
ifeq ($(DEBUGGER),0)
DEBUGGER_CFG = "C:\Program Files (x86)\GNU Arm Embedded Toolchain\xpack-openocd-0.12.0-2\openocd\scripts\interface\stlink.cfg"
else 
DEBUGGER_CFG = "C:\Program Files (x86)\GNU Arm Embedded Toolchain\xpack-openocd-0.12.0-2\openocd\scripts\interface\jlink.cfg"
endif
endif

TRANSPORT_SEL := -c "transport select swd"

# test : 
# 	$(info Current DEBUGGER is $(DEBUGGER))
# 	$(info Current DEBUGGER_CFG is $(DEBUGGER_CFG))

OPENOCD_DEBUG_CMDS = 
OPENOCD_DEBUG_CMDS += -c "reset halt"
OPENOCD_DEBUG_CMDS += -c "flash write_image erase $(TARGET).elf"
#OPENOCD_DEBUG_CMDS += -c "program $(TARGET).elf verify reset exit"
OPENOCD_DEBUG_CMDS += -c "reset"

OPENOCD_DEBUG_CMDS += -c "shutdown"


loadserver :
	$(OPENOCD) -f  $(DEBUGGER_CFG) \
	       	-f  $(CHIP_CFG) &
#			 $(MSG_SUPRESS) &

monitor :
	$(START) $(OPENOCD) -f  $(DEBUGGER_CFG) \
	       	-f  $(CHIP_CFG) 
	
	$(START) $(GDB_CMD) \
		-ex "target remote localhost:3333" \
		-ex "monitor arm semihosting enable" \
		-ex "detach" \
		-ex "quit"    \
		$(MSG_SUPRESS) &

run : $(TARGET).elf
	@$(call COL,$(GREEN),Running $<)
	@$(OPENOCD) -f $(DEBUGGER_CFG) -f $(CHIP_CFG) -c init -c "reset" -c "shutdown"


flash :
	@$(OPENOCD) -f  $(DEBUGGER_CFG) \
			$(TRANSPORT_SEL) \
	       	-f  $(CHIP_CFG) \
			-c init $(OPENOCD_DEBUG_CMDS)

gdbflash : loadserver
	$(START) $(GDB_CMD) \
		-ex "target remote localhost:3333" \
		-ex "monitor reset halt" \
		-ex "monitor flash write_image erase ./final.elf" \
		-ex "detach" \
		-ex "quit"

gdbdbg : 
	 $(GDB) \
		-ex "file ./$(TARGET).elf" \
		-ex "target remote localhost:3333" \
		-ex "monitor reset halt" \
		-ex "source ./svd_tool/gdb-svd.py" \
		-ex "svd ./svd_tool/STM32F103xx.svd" \
