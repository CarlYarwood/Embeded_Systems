	#define __SFR_OFFSET 0
	#include <avr/io.h>

	.global addflags
	.global subflags
	;; Project 2 Subroutines
	;; Carl Yarwood
	;; This file defines two functions
	;; both of which take in two 8 bit numbers
	;; one adds the other subtracts, and then
	;; the 8 bit sreg is returned

	;; additon function
	;; does a+b and returns
	;; the status register
	;; from given operation
addflags:
	add r24, r22		;addition
	in r24, SREG		;avr/io.h defines sreg in io space, SREG -> r24
	ret

	;; This subroutine takes the
	;; given numbers and preforms
	;; subtraction returning the
	;; status register from the
	;; given operation
subflags:
	sub r24, r22   		;subtriaction
	in r24, SREG		;avr/io.h defines sreg in io space, SREG -> r24
	ret
