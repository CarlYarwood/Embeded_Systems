lab4.hex: lab4.elf
	avr-objcopy -j .text -j .data -O ihex lab4.elf lab4.hex

lab4.elf: lab4.o
	avr-gcc -mmcu=atmega328p lab4.o -o lab4.elf

lab4.o: lab4.c
	avr-gcc -mmcu=atmega328p -c lab4.c -o lab4.o

install: lab4.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:lab4.hex:i

clean:
	rm -f *.hex *.elf *.o *~
