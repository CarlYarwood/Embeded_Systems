	;; Project 01 Walking LEDs
	;; Carl Yarwood
	;; This program in meant to be run on an arduino uno or other similar
	;; system
	;; This program cascades high voltage from port d0 - port d7 which can
	;; be used for a cascading led effect,
	;; it will cascade d0 -> d7 if low voltage is on pin c0
	;; it will cascade d7 -> d0 if high voltage is on pin c0
	;; voltage on pin c0  can be swapped during runtime to dynamically
	;; change the directoin of the cascade, note the cascade will loop
	.equ	PINC, 0x06
	.equ	DDRC, 0x07
	.equ	PORTC, 0x08
	.equ    DDRD, 0x0a
	.equ    PORTD, 0x0b

	.text
main:
	ldi r28, 0x01		;initial light setup
	;; setup reg D
	ldi r29, 0xff
	out DDRD, r29		;all pins on reg d output
	;; set up reg C
	cbi DDRC, 0
loop:
	out PORTD, r28		;output current light
	call delay
	in r29, PINC		;recive input from pinC
	andi r29, 0x01		;isolate bit corresponding to c0
	cpi r29, 0x01
	clc			;clear any carry bit cause by comparison
	breq else		;branch to else if high voltage on c0
	rol r28
	brcc continue		;skip next intruction if carry bit 0
	rol r28			;rol carry bit back into r28
	jmp continue		;jump to after alternate case
else:
	ror r28
	brcc continue		;skip next instruction if carry bit zero
	ror r28			;ror carrybit back into r28
continue:	
	out PORTD, r28
	call delay
	jmp loop



delay:
	ldi r31, 0xff
	ldi r30, 0xff
delay1:
	nop
	nop
	nop
	nop
	nop
	nop
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
