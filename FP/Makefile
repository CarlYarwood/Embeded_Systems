# Carl Yarwood
simon.hex: simon.elf
	avr-objcopy -j .text -j .data -O ihex simon.elf simon.hex

simon.elf: simon.o delay.o
	avr-gcc -mmcu=atmega328p simon.o delay.o -o simon.elf

simon.o: simon.c delay.h
	avr-gcc -mmcu=atmega328p -c simon.c -o simon.o

delay.o: delay.S
	avr-gcc -mmcu=atmega328p -c delay.S -o delay.o

install: simon.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:simon.hex:i

clean:
	rm -f *.o *.elf *.hex *~
