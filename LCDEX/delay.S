	.macro nop2			;
	rjmp .				;
	.endm				;

	.text
	.global delay1us
	.global delay1ms

delay1us:
	nop
	nop2
	rjmp delay2
delay1:
	nop2
	nop2
	nop2
	nop2
	nop2
	nop2
delay2:
	sbiw r24, 1
	brne delay1
	ret

delay1ms:
	movw r26, r24
	rjmp delay4
delay3:
	nop2
	nop2
	nop2
	nop2
	nop2
delay4:
	ldi r24, 231
	ldi r25, 3
	call delay1us
	sbiw r26, 1
	brne delay3
	ret
