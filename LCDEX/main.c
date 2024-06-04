#include <avr/io.h>
#include "lcd.h"
#include "delay.h"

void main(){
  lcdInit(DDRD, PORTD, DDRB, PORTB, 1<<PD6, 1<<PD7, 1<<PB0, 1<<PB1, 1<<PB2, 1<<PB3);
  lcdPuts("Hello, World!");
  delay1ms(1000);
  while(1){}
}
