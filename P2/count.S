	#define __SFR_OFFSET 0
	#include <avr/io.h>
	;; Project 2 Subroutines counting main method
	;; Carl Yarwood
	;; this loops through a binary counting
	;; operation calling the c function ledbyte
	;; located in ledbyte.c to present the output

	.global main
main:
	ldi r29, 0xff
	out DDRD, r29		;sets up DDRD
	ldi r29, 0x01		;inits r29
loop:
	mov r24, r29		;coppies r29 to r24
	call ledbyte		;outputs r24 to led
	inc r29			;increments r29
	call delay
	call delay
	jmp loop
delay:
	ldi r31 , 0xff
	ldi r30, 0xff
delay1:
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	sbiw r30, 1
	brne delay1

	ret
