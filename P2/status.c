#include <avr/io.h>
#include "ledbyte.h"
#include "mathflags.h"
/*
  Project 2 routines
  Carl Yarwood
  Mainfile for presenting SREG
  calls a given math flag on a
  series of values to obtain a
  certain SREG which it outputs
  by calling ledbyte, it then
  ouputs the result of the
  calculation by calling ledbyte
  on the calculation preformed
  in the subroutine to get the 
  sreg
*/

void delay();

void main(){
  //set portD to output
  DDRD = 0xff;
  while(1){
    //sreg output for set z flag
    ledbyte(subflags(0x01, 0x01));
    delay();
    ledbyte(0x01 - 0x01);
    delay();
    //sreg output for set h flag
    ledbyte(addflags(0x0f,0x01));
    delay();
    ledbyte(0x0f + 0x01);
    delay();
    //sreg output for set c flag
    ledbyte(addflags(0xf0,0x11));
    delay();
    ledbyte(0xf0 + 0x11);
    delay();
    //sreg output for set s,n flags
    ledbyte(subflags(0xf0,0x10));
    delay();
    ledbyte(0xf0 - 0x10);
    delay();
    //sreg output for set v,n flags
    ledbyte(addflags(0x70, 0x10));
    delay();
    ledbyte(0x70 + 0x10);
    delay();
    //sreg output for set z,c flags
    ledbyte(addflags(0xf0,0x10));
    delay();
    ledbyte(0xf0 + 0x10);
    delay();
    //sreg flag for s,v,c flags
    ledbyte(addflags(0x80, 0x81));
    delay();
    ledbyte(0x80 + 0x81);
    delay();
  }
}

/*
  This functions provides aproximately
  6-7 seconds of busy waiting
*/
void delay(){
  volatile uint16_t i;
  volatile uint16_t j;
  for(i=65535U; i!= 0; i--){
      for(j=64U; j!= 0; j--){}
  }
}
