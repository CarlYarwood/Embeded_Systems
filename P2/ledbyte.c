/*
  Project 02 Subroutines led output
  Carl Yarwood
  this contains the sub routine to ouput
  a given 8 bits  to corresponding leds
  1 turns the led 0, 0 turns it off
 */
#include <avr/io.h>
#include "ledbyte.h"

void ledbyte(uint8_t b){
  PORTD = b;
  return;
}
