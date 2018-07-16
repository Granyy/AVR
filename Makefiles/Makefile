TARGET=myTarget
SRC=$(shell find . -name '*.c')
OBJ=$(SRC:.c=.o)

CROSS=avr-
CC=$(CROSS)gcc
OBJCOPY=$(CROSS)objcopy
SIZE=$(CROSS)size

AVRTYPE=attiny84
CFLAGS=-g -Wall -Os -mmcu=$(AVRTYPE)

AVRFLASH_TYPE=t84
PROGRAMMER_DEV=usb
PROGRAMMER_TYPE=usbasp

all: $(TARGET).elf bin hex size

clean:
	@echo " CLEAN"
	@rm $(TARGET).elf $(TARGET).hex $(TARGET).bin $(OBJ)

%.o: %.c
	@echo " CC       $<"
	@avr-gcc $(CFLAGS)  -o $@ -c $<


$(TARGET).elf: $(OBJ)
	@echo " LD       $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJ)

hex: $(TARGET).elf
	@echo " OBJCOPY  $(TARGET:.elf=.hex)"
	@$(OBJCOPY) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

bin: $(TARGET).elf
	@echo " OBJCOPY  $(TARGET:.elf=.bin)"
	@$(OBJCOPY) -j .text -j .data -O binary $(TARGET).elf $(TARGET).bin

size:
	@$(SIZE) --format=berkeley $(TARGET).elf

flash: hex
	avrdude -P$(PROGRAMMER_DEV) -p$(AVRFLASH_TYPE) -c$(PROGRAMMER_TYPE) -U flash:w:$(TARGET).hex