main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf: main.o showBytes.o setLowAndTime.o delay.o
	avr-gcc -mmcu=atmega328p main.o showBytes.o setLowAndTime.o delay.o -o main.elf

main.o: main.c setLowAndTime.h showBytes.h
	avr-gcc -mmcu=atmega328p -c main.c -o main.o

showBytes.o: showBytes.c delay.h
	avr-gcc -mmcu=atmega328p -c showBytes.c -o showBytes.o

setLowAndTime.o: setLowAndTime.S
	avr-gcc -mmcu=atmega328p -c setLowAndTime.S -o setLowAndTime.o

delay.o: delay.S
	avr-gcc -mmcu=atmega328p -c delay.S -o delay.o

lab4.hex: lab4.elf
	avr-objcopy -j .text -j .data -O ihex lab4.elf lab4.hex

lab4.elf: lab4.o
	avr-gcc -mmcu=atmega328p lab4.o -o lab4.elf

lab4.o: lab4.c
	avr-gcc -mmcu=atmega328p -c lab4.c -o lab4.o

install-part1: lab4.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:lab4.hex:i

install-part2: main.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:main.hex:i

clean:
	rm -f *.hex *.elf *.o *~
