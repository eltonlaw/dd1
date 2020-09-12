.PHONY: all build flash

MCU =
F_CPU =
BAUD =
PORT = /dev/ttyACM0

all: build flash

build:
	# Generates assembly code
	avr-gcc -g -Os -Wall -mcall-prologues -mmcu=atmega328 -S -o main.s main.c
	# Generate object code
	avr-gcc -g -Os -Wall -mcall-prologues -mmcu=atmega328 -c -o main.o main.c
	avr-gcc -g -Os -Wall -mcall-prologues -mmcu=atmega328 main.o -o main.obj
	# Remove eeprom section and translate to intel hex
	avr-objcopy -R .eeprom -O ihex main.obj main.hex

flash:
	avrdude -c avrispv2 -p m328p -P $(PORT) -e -v -U flash:w:main.hex

clean:
	rm -f *.elf *.obj *.hex *.o *.s
