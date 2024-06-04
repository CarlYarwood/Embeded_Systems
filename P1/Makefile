yarwood1.hex: yarwood1.elf
	avr-objcopy -j .text -j .data -O ihex yarwood1.elf yarwood1.hex

yarwood1.elf: yarwood1.o
	avr-ld yarwood1.o -o yarwood1.elf
	avr-strip yarwood1.elf

yarwood1.o: yarwood1.S
	avr-as -mmcu=atmega328p yarwood1.S -o yarwood1.o

install: yarwood1.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:yarwood1.hex:i

clean:
	rm -f *.o *.elf *.hex *.lst
