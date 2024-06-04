count.hex: count.elf
	avr-objcopy -j .text -j .data -O ihex count.elf count.hex

count.elf: ledbyte.o count.o
	avr-gcc -mmcu=atmega328p count.o ledbyte.o -o count.elf

count.o: count.S
	avr-gcc -mmcu=atmega328p -c count.S -o count.o

status.hex: status.elf
	avr-objcopy -j .text -j .data -O ihex status.elf status.hex

status.elf: ledbyte.o mathflags.o status.o
	avr-gcc -mmcu=atmega328p status.o mathflags.o ledbyte.o -o status.elf

status.o: status.c mathflags.h ledbyte.h
	avr-gcc -mmcu=atmega328p -c status.c -o status.o

mathflags.o: mathflags.S
	avr-gcc -mmcu=atmega328p -c mathflags.S -o mathflags.o

ledbyte.o: ledbyte.c ledbyte.h
	avr-gcc -mmcu=atmega328p -c ledbyte.c -o ledbyte.o

install-count: count.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:count.hex:i

install-status: status.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:status.hex:i

clean:
	rm -f *.hex *.elf *.o *~
