#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "delay.h"

/*
Final Project Simon
By Carl Yarwood
Simon is a game that test memory,
this is made to be set up on the arduino uno,
for wring details and an explanation of the rules, reference
the pdf turned in where that is described.
*/
#define GREENBUTTON (1<<PCINT17)
#define YELLOWBUTTON (1<<PCINT19)
#define REDBUTTON (1<<PCINT21)
#define BLUEBUTTON (1<<PCINT23)
#define GREENLIGHT (1<<PD0)
#define YELLOWLIGHT (1<<PD2)
#define REDLIGHT (1<<PD4)
#define BLUELIGHT (1<<PD6)

volatile uint8_t pressed_recently = 0;
volatile uint8_t game_ongoing = 1;
volatile char* position;
volatile uint8_t length = 0;
volatile uint8_t num_correct = 0;
volatile uint16_t idle_counter = 0;

void play_green_noise();
void play_yellow_noise();
void play_red_noise();
void play_blue_noise();
void stop_noise();
void prevent_button_bounce();
uint8_t rand_2_bits();
void indicate_win();
void indicate_loss();
void generate_sequence(char* seq);
void play_sequence(char* seq);

/*
This ISR is run on timer 1, it prevents
button bounce note the sleep_cpu at the end
because this is on timer 1, cpu must not be
sleeping for debounce to work properly, this
should run aproximatly 50 ms after a button
press
*/
ISR(TIMER1_COMPA_vect){
  pressed_recently = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  OCR1A = 0;
}
/*
Timer 2 is th only timer which can run while
cpu is in idle, as such timer2 handels going
into deep sleep to preserve power consumption
this runs about 30 seconds after being left idle,
note after entering deep sleep a power cycle or
reset is required to re-start
 */
ISR(TIMER2_OVF_vect){
  idle_counter++;
  if(idle_counter >= 1831){
    sleep_disable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
  }
}
/*
This is the Primary ISR, it detects
button presses and handels
the accordingly
 */  
ISR(PCINT2_vect){
  //helper for button debounce
  if(pressed_recently==0){
    uint8_t in = PIND;
    //green button press
    if(~in & GREENBUTTON){
      idle_counter = 0;
      if(*position == 'g'){
	PORTD |= GREENLIGHT;
        play_green_noise();
	position++;
	num_correct++;
	if(num_correct >= length){
	  indicate_win();
	}
      }
      else{
	indicate_loss();
      }
    }
    //yellow button press
    else if(~in & YELLOWBUTTON){
      idle_counter = 0;
      if(*position == 'y'){
	PORTD |= YELLOWLIGHT;
        play_yellow_noise();
	position++;
	num_correct++;
	if(num_correct == length){
	  indicate_win();
	}
      }
      else{
	indicate_loss();
      }
    }
    //red button press
    else if( ~in & REDBUTTON){
      idle_counter = 0;
      if(*position == 'r'){
	PORTD |= REDLIGHT;
        play_red_noise();
	position++;
	num_correct++;
	if(num_correct == length){
	  indicate_win();
	}
      }
      else{
	indicate_loss();
      }
    }
    //blue button press
    else if(~in & BLUEBUTTON){
      idle_counter = 0;
      if(*position == 'b'){
	PORTD |= BLUELIGHT;
        play_blue_noise();
	position++;
	num_correct++;
	if(num_correct == length){
	  indicate_win();
	}
      }
      else{
	indicate_loss();
      }
    }
    //any button released
    else{
      PORTD &= ~GREENLIGHT & ~REDLIGHT &~YELLOWLIGHT & ~BLUELIGHT;
      stop_noise();
      idle_counter = 0;
    }
    //helper function to prevent button bounce
    prevent_button_bounce();
  }
}

int main(){
  //audio output
  DDRB |= (1<<PB3);
  //light outpu
  DDRD = GREENLIGHT | YELLOWLIGHT | REDLIGHT | BLUELIGHT;
  //activate internal pull up resistors for button circuits
  PORTD |= GREENBUTTON | YELLOWBUTTON | REDBUTTON | BLUEBUTTON;
  //set up pin change interupts for buttons
  PCICR = (1<<PCIE2);
  PCMSK2 = GREENBUTTON | YELLOWBUTTON | REDBUTTON | BLUEBUTTON;
  //set up adc for random number generation
  ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADMUX = (1<<REFS0);
  //set up timer 2 for idle timeout
  TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20);
  //set up general sleep mode for power savings while playing
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
  //max sequence is 50 lights
  char seq[50];
  while(1){
    //initialize a round of the game
    cli();
    //pause idle timer
    TIMSK2 = (1<<TOIE2);
    game_ongoing = 1;
    num_correct = 0;
    if(length != 50){
      length ++;
    }
    generate_sequence(seq);
    position = seq;
    play_sequence(seq);
    //start idle timer
    TIMSK2 = (1<<TOIE2);
    sei();
    //cpu sleeps here instead of in loop
    //so button de-bounce works
    //it sleeps on idle until interaction
    sleep_cpu();
    while(game_ongoing == 1){
    }
  }
}

/*
uses timer 2 pwm to play noise
associated with green light
and loss
*/
void play_green_noise(){
  //take timer 2 off idle count
  TIMSK2 = 0x00;
  //play noise
  OCR2A = 255;
  TCCR2A = (1<<WGM21)|(1<<COM2A0);
  TCCR2B = (1<<CS20)|(1<<CS21)|(1<<CS22);
}

/*
uses timer 2 pwm to play noise
associated with yellow light
*/
void play_yellow_noise(){
  //take timer 2 off idle count
  TIMSK2 = 0x00;
  //play noise
  OCR2A = 127;
  TCCR2A = (1<<WGM21)|(1<<COM2A0);
  TCCR2B = (1<<CS20)|(1<<CS21)|(1<<CS22);
}

/* 
uses timer 2 pwm to play noise associated
with red light
 */
void play_red_noise(){
  //take timer 2 off idle count
  TIMSK2=0x00;
  //play noise
  OCR2A = 63;
  TCCR2A = (1<<WGM21)|(1<<COM2A0);
  TCCR2B = (1<<CS20)|(1<<CS21)|(1<<CS22);
}
/*
uses timer 2 pwm to play noise associated
with blue light and winning a round
 */
void play_blue_noise(){
  //take timer 2 off of idle count
  TIMSK2 = 0x00;
  //play noise
  OCR2A = 31;
  TCCR2A = (1<<WGM21)|(1<<COM2A0);
  TCCR2B = (1<<CS20)|(1<<CS21)|(1<<CS22);
}
void stop_noise(){
  OCR2A = 0;
  TCCR2A = 0x00;
  TIMSK2 = (1<<TOIE2);
  TCCR2B = (1<<CS22)|(1<<CS21)| (1<<CS20);
}
/*
disables buttons and
sets up timer 1 to interrupt aproximately
50ms after run to re-activate buttons
*/
void prevent_button_bounce(){
  //button deactivation
  pressed_recently = 1;
  //timer setup
  OCR1A = 12500;
  TCCR1A = 0x00;
  TCCR1B = (1<<WGM12)|(1<<CS11)|(1<<CS10);
  TIMSK1 = (1<< OCIE1A);
}

/*
uses adc on open open port
to generate 2 random bits
*/
uint8_t rand_2_bits(){
  uint8_t rand = 0;
  for(uint8_t i = 0; i<2; i++){
    rand <<= 1;
    //start adc
    ADCSRA |= (1<<ADSC);
    //wait for adc to be done
    while((ADCSRA & (1<<ADIF)) == 0);

    //reset adc to run again later
    ADCSRA |= (1<<ADIF);
    uint8_t lo = ADCL;
    uint8_t hi = ADCH;
    //take bottom bit of adc and apend
    //to random number
    rand |= lo&1;
  }
  return rand;
}

/*
utilizes random number generated by 
adc to generate a sequence of size determined
by global length
length is global so I have access to it in 
ISR
 */
void generate_sequence(char* seq){
  for(uint8_t i = 0; i < length; i++){
    uint8_t choice = rand_2_bits()%4;
    if(choice == 0){
      seq[i] = 'g';
    }
    else if(choice == 1){
      seq[i] = 'y';
    }
    else if(choice == 2){
      seq[i] = 'r';
    }
    else{
      seq[i] = 'b';
    }
  }
}

/*
plays given sequence for as long
as global length, playing each light/sound
for 1 second followed by a half second pause
 */
void play_sequence(char * seq){
  for(uint8_t i = 0; i<length ;i++){
    if(seq[i] == 'g'){
      PORTD |= GREENLIGHT;
      play_green_noise();
      delay1ms(1000);
      stop_noise();
      PORTD &= ~GREENLIGHT;
    }
    else if(seq[i] == 'y'){
      PORTD |= YELLOWLIGHT;
      play_yellow_noise();
      delay1ms(1000);
      stop_noise();
      PORTD &= ~YELLOWLIGHT;
    }
    else if(seq[i] == 'r'){
      PORTD |= REDLIGHT;
      play_red_noise();
      delay1ms(1000);
      stop_noise();
      PORTD &= ~REDLIGHT;
    }
    else if(seq[i] == 'b'){
      PORTD |= BLUELIGHT;
      play_blue_noise();
      delay1ms(1000);
      stop_noise();
      PORTD &= ~BLUELIGHT;
    }
    delay1ms(500);
  }
}

/*
Indicate you have fully
succesfully answered a round
 */
void indicate_win(){
  PORTD |= GREENLIGHT;
  play_green_noise();
  delay1ms(250);
  PORTD |= YELLOWLIGHT;
  play_yellow_noise();
  delay1ms(250);
  PORTD |= REDLIGHT;
  play_red_noise();
  delay1ms(250);
  PORTD |= BLUELIGHT;
  play_blue_noise();
  delay1ms(250);
  stop_noise();
  PORTD &= ~GREENLIGHT & ~YELLOWLIGHT & ~REDLIGHT & ~BLUELIGHT;
  game_ongoing = 0;
}

/*
indicates you have lost a round
*/
void indicate_loss(){
  play_green_noise();
  PORTD |= GREENLIGHT | YELLOWLIGHT | REDLIGHT | BLUELIGHT;
  delay1ms(1000);
  stop_noise();
  PORTD &= ~GREENLIGHT & ~YELLOWLIGHT & ~REDLIGHT & ~BLUELIGHT;
  game_ongoing = 0;
  length = 0;
}
  
