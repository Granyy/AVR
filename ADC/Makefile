src=main
avrType=attiny84
avrFlashType=t84
programmerDev=usb
programmerType=usbasp

cflags=-g -Wall -Os

edit:
	nano $(src).c

clean: 
	rm $(src).elf $(src).flash.hex $(src).o
object:
	avr-gcc $(cflags) -mmcu=$(avrType) -c -o $(src).o $(src).c

elf: object
	avr-gcc $(cflags) -mmcu=$(avrType) -o $(src).elf $(src).o
	chmod a-x $(src).elf 2>&1

hex: elf
	avr-objcopy -j .text -j .data -O ihex $(src).elf $(src).flash.hex

program: flash clean

flash: hex
	avrdude -P$(programmerDev) -p$(avrFlashType) -c$(programmerType) -U flash:w:$(src).flash.hex
