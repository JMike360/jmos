
SRCS= main.c
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size
PROJECT=jmos

## General compiler flags ##
CFLAGS = -Wall -Werror -std=c99 -g -Tjmos-stm32-link.ld
CFLAGS += -ffunction-sections -fdata-sections 
CFLAGS += -I.

## STM32 required flags ##
CFLAGS += -mlittle-endian -mcpu=cortex-m0 -march=armv6-m -mthumb -mthumb-interwork
#CFLAGS += --specs=nosys.specs #Some issue with newlib includes related to _exit() causes the compiler to throw errors without this. I suspect the stm32 CMSIS package has includes to replace certain standard C implementations, but for now we will use this semihosting config option.

## Optional configuration flags ##

#I like the idea of consistent fn call frames, but I have no idea whether to use
# -mapcs-frame for ARM Proc call std or -mtpcs-frame for Thumb Proc call std
#CFLAGS += -mapcs-frame 
#CFLAGS += -mtpcs-frame
#CFLAGS += -Os #Optimize for space, not needed rn
CFLAGS += -ffreestanding -nostdlib
#####################################################################################

OBJS = $(SRCS:.c=.o)

.PHONY: project

all: project

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

asm: $(OBJS)

project: $(PROJECT).elf

$(PROJECT).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin
	$(OBJDUMP) -St $(PROJECT).elf >$(PROJECT).lst
	$(SIZE) $(PROJECT).elf

clean:
	rm -f *.o $(PROJECT).elf $(PROJECT).hex $(PROJECT).bin $(PROJECT).lst

flash:
	st-flash write $(PROJECT).bin 0x08000000
