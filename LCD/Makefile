lcd.o : lcd.c lcd.h delay.h
	avr-gcc -mmcu=atmega328p -c lcd.c -o lcd.o
delay.o: delay.S
	avr-gcc -mmcu=atmega328p -c delay.S -o delay.o
