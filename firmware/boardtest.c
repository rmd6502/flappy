/*
 * boardtest.c
 *
 * Created: 3/23/2014 10:53:08 AM
 *  Author: rmd
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define NUM_SERVOS 11
volatile int servopwm[NUM_SERVOS];
volatile uint8_t servoindex;

void setup();
int main(void)
{
	setup();
    while(1)
    {
		for (int i=900; i < 2100; i += 6) {
			for (int index=0; index < NUM_SERVOS; ++index) {
				servopwm[index]	= i;
			}
			_delay_ms(5);
		}
		for (int i=2100; i > 900; i -= 6) {
			for (int index=0; index < NUM_SERVOS; ++index) {
				servopwm[index]	= i;
			}
			_delay_ms(5);
		}
    }
}

// This code copyright Shane Colton, from http://scolton.blogspot.com/2010/07/arduino-interrupt-driven-servo-routine.html
//
void setup()
{
	// TIMER1 SETUP FOR SERVOS
	// -----------------------
	// set Timer1 to clk/64 and 9-bit fast PWM
	// this is a period of 2.048ms for 16MHz clk
	// when multiplexed on 8 servos, this gives a 16ms period
	// RMD: clk/8 for 8MHz = 1MHz and fast PWM with ICR1 = 2100
	cli();
	ICR1 = 2100;
	TCNT1 = 0;
	TCCR1A = (0x02 << WGM10);
	// enable Timer1 compare match and overflow interrupts
	TIMSK1 = 0x03;
	// -----------------------
	
	// set initial servo index
	servoindex = 0;
	TCNT1 = ICR1 - 64;	// so we overflow first
	
	// set all servos to neutral (375 = 1.500ms)
	for (int i=0; i < NUM_SERVOS; ++i) {
		servopwm[i] = 1500;
	}
	
	// set all servo pins to outputs
	PORTA = 0;
	PORTB = 0;
	DDRA = 0xff;
	DDRB = 0x07;
	
	// start the clock last
	TCCR1B = (0x03 << WGM12) | (2 << CS10);
	sei();
}
// INTERRUPT SERVICE ROUTINES
// --------------------------

ISR(TIM1_COMPA_vect)
{
	// interrupt on Timer1 compare match
	// (end of the servo pulse)
	
	// end servo pulse on the appropriate pin
	// faster version of digitalWrite(servoindex, LOW);
	if(servoindex <= 7)
	{
		PORTA &= ~(1 << servoindex);
	}
	else
	{
		PORTB &= ~(1 << (servoindex - 8));
	}
	
	// move on to the next servo (limit to 2-8)
	servoindex++;
	if(servoindex == NUM_SERVOS)
	{
		servoindex = 0;
	}
	
	// set the compare match to the new servo pulse duration
	OCR1A = servopwm[servoindex];

	return;
}

ISR(TIM1_OVF_vect)
{
	// interrupt on Timer1 overflow
	// start of the next servo pulse
	
	// start servo pulse on the appropriate pin
	// faster version of digitalWrite(servoindex, HIGH);
	if(servoindex <= 7)
	{
		PORTA |= (1 << servoindex);
	}
	else
	{
		PORTB |= (1 << (servoindex - 8));
	}
	
	return;
}
// --------------------------