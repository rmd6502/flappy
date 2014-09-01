#include <Servo.h>

#include "flappy.h"


Servo rollingServo;

#define NUM_SAMPLES 16
uint16_t samples[NUM_SAMPLES] = {0};
uint32_t sum = 0;
uint8_t index = 0;

void setup()
{
//  // differential input = (ADC1-ADC3) * 20, vcc reference
//  ADMUX = (15 << MUX0) | (2 << REFS0);
//  // Enable ADC, 64x prescaler
//  ADCSRA = _BV(ADEN) | (6 << ADPS0);
//  // ADC3 is pulled at ~2.5v
//  ADCSRB = 0;
//  // start conversion
//  ADCSRA  |= _BV(ADSC);
//  
//  DIDR0 = _BV(ADC1D) | _BV(ADC3D);
  pinMode(hall_input, INPUT);
  rollingServo.attach(roll_servo);
  Serial1.begin(115200);
  Serial1.println("Starting...");
}

void loop()
{
  static uint16_t last = 0;
  uint16_t reading = 0;
  // Has the conversion finished?
  
    reading = analogRead(hall_input);
    sum -= samples[index];
    sum += reading;
    samples[index++] = reading;
    if (index == NUM_SAMPLES) {
      index = 0;
    }
    uint16_t average = sum/NUM_SAMPLES;
    int16_t delta = average - last;
    last = average;
    rollingServo.write(map(average, 275,330, 45,135));
    Serial1.print(average);Serial1.print("  ");Serial1.println(delta);
    delay(100);
}
