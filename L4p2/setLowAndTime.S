	#define __SFR_OFFSET 0
	#include <avr/io.h>
	.text
	.global setLowAndTime  ;    uint32_t setLowAndTime()
setLowAndTime:
	clr r22           ; initialize r22:r25 registers to zero
	clr r23           ; we’ll use them to count microseconds
	clr r24
	clr r25
	ldi r20, 1        ; for incrementing with carry
	cbi PORTB, PB1    ; set PB1 low
loop1:
	in r21, PINB		;1 cycle
	andi r21, (1<<PB0) ; see if PB0 is low 1 cycle
	breq done1        ; and break the loop if it is 1 cycle if false
	add r22, r20      ; add one to the count 1 cycle
	adc r23, r1       ;  and carry 1 cycle
	adc r24, r1       ;  and carry 1 cycle
	adc r25, r1       ;  and carry into MSB 1 cycle
	nop               ; delay 1 cycle
	rjmp .            ; delay 2 cycles
	rjmp .            ; delay 2 cycles
	rjmp .            ; delay 2 cycles
	rjmp loop1
done1:
	sbi PORTB, PB1    ; set PB1 high again
	ret
	
