# :set noet
PROJ_NAME = steering

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS  = -O0 -Wall -Wextra -Wstrict-prototypes -Werror -std=gnu11
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -march=armv7-m
CFLAGS += -msoft-float
CFLAGS += -I./inc -nostdlib -fno-builtin
CFLAGS += -T./STM32F205xx/STM32F205xB.ld
CFLAGS += -I./inc/boards -I./inc/stm32 -I./inc/drivers

# debug
CFLAGS += -g
CFLAGS += -DDEBUG_UART

SRC ?=

# CMSIS
CMSIS_DIR = STM32F205xx/CMSIS/STM32F2xx
CFLAGS += -I./$(CMSIS_DIR)/../ARM/inc -I./$(CMSIS_DIR)/inc
CFLAGS += -DSTM32F2 -DSTM32F205xx -DCALL_ARM_SYSTEM_INIT
SRC += ./$(CMSIS_DIR)/src/*.c

# HAL
HAL_DIR = STM32F205xx/HAL/STM32F2xx
CFLAGS += -I./$(HAL_DIR)/inc -DUSE_HAL_DRIVER
#HAL_SRC := $(shell find $(HAL_DIR)/src/*.c ! -name '*_template.c')
#SRC += $(HAL_SRC)
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_cortex.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_rcc.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_gpio.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_flash.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_flash_ex.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_dma.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_dma_ex.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_pwr.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_pwr_ex.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_uart.c
SRC += ./$(HAL_DIR)/src/stm32f2xx_hal_iwdg.c


SRC += ./src/*.c

BIN_FILE = obj/$(PROJ_NAME).bin
ELF_FILE = obj/$(PROJ_NAME).elf
OBJ_FILE = obj/startup_stm32f205xx.o

.PHONY: all
all: obj/$(PROJ_NAME).bin

$(BIN_FILE): $(ELF_FILE)
	$(OBJCOPY) -O binary $^ $@

$(ELF_FILE): $(SRC) $(OBJ_FILE)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_FILE): STM32F205xx/startup/STM32F205xx.s
	$(CC) $(CFLAGS) -c $< -o $@

flash:
	st-flash write $(BIN_FILE) 0x08000000

clean:
	rm -f obj/*
