;;; David Blanck & Carl Yarwood
;;; delay.S
;;; A program which implements two precise delay functions

	.text
.macro nop2
	rjmp .
.endm


;;; delays 16 clock cycles per iteration
;;; For the Arduino Uno, 16 clock cycles delays 1 microsecond
;;; Specify the number of iterations by parameter
	
.global delay1us	; void delay1us( unsigned n )
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

;;; delays 16000 clock cycles per iteration
;;; For the Arduino Uno, 16000 clock cycles delays 1 millisecond
;;; Specify the number of iterations by parameter
	
.global delay1ms 	; void delay1ms ( unsigned n )
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
