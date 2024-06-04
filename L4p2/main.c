#include <avr/io.h>
#include "showBytes.h"
#include "setLowAndTime.h"
#include "delay.h"

void main(){
  DDRB = (1<<PB5) | (1<<PB1);
  DDRD = 0xff;
  PORTB = (1<<PB1);
  delay1ms(500);

  uint32_t n = setLowAndTime();
  delay1ms(5000);
  showBytes(n);
  while(1);
}
