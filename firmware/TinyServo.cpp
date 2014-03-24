#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>

#include "TinyServo.h"

extern SoftwareSerial mySerial;

static volatile uint16_t servopwm[NUM_SERVOS];
static volatile uint8_t servoindex;
static volatile uint8_t attached[NUM_SERVOS];

TinyServo tinyServo;

TinyServo::TinyServo()
{
  for (uint8_t pin=0; pin < NUM_SERVOS; ++pin) {
    attached[pin] = 0;
  }
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
		servopwm[i] = 0;
	}
	
	// start the clock last
	TCCR1B = (0x03 << WGM12) | (2 << CS10);
	sei();
}

void TinyServo::attach(uint8_t servoNumber)
{
  digitalWrite(servoNumber, LOW);
  pinMode(servoNumber, OUTPUT);
  attached[servoNumber] = 1;
}

void TinyServo::detach(uint8_t servoNumber)
{
  attached[servoNumber] = 0;
}

void TinyServo::write(uint8_t servoNumber, float angle)
{
  uint16_t count = 900 + (1200.0f * angle / 180.0f);
  mySerial.print("count "); mySerial.println(count);
  if (count < 900) {
    count = 900;
  }
  if (count > 2100) {
    count = 2100;
  }
  servopwm[servoNumber] = count;
}

// INTERRUPT SERVICE ROUTINES
// --------------------------

ISR(TIM1_COMPA_vect)
{
	// interrupt on Timer1 compare match
	// (end of the servo pulse)
	
	// end servo pulse on the appropriate pin
	// faster version of digitalWrite(servoindex, LOW);
        if (attached[servoindex]) {
        	if(servoindex <= 7)
        	{
        		PORTA &= ~(1 << servoindex);
        	}
        	else
        	{
        		PORTB &= ~(1 << (10-servoindex));
        	}
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
        if (attached[servoindex]) {
        	if(servoindex <= 7)
        	{
        		PORTA |= (1 << servoindex);
        	}
        	else
        	{
        		PORTB |= (1 << (10-servoindex));
        	}
        }
	
	return;
}
