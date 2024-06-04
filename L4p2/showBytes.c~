#include <avr/io.h>
#include "delay.h"

void showBytes(uint32_t n){
  PINB |= (1<<PB5);  //toggle board LED
  PORTD = (n>>24);  //show high byte
  delay1ms(5000);

  PINB |= (1<<PB5);  //toggle board LED
  PORTD = (n>>16);  // show second byte
  delay1ms(5000);

  PINB |= (1<<PB5); //toggle borad LED
  PORTD = (n>>8); //show third byte
  delay1ms(5000);

  PINB |= (1<< PB5); //toggle board led
  PORTD = (n>>0); //show low byte
  delay1ms(5000);
}
