#include <SoftwareSerial.h>

static const uint8_t analog1 = 2;
static const uint8_t analog2 = 5;

SoftwareSerial mySerial(4,0);

#define NUM_SAMPLES 16
uint16_t samples[NUM_SAMPLES] = {0};
uint32_t sum = 0;
uint8_t index = 0;

void setup()
{
  // differential input = (ADC1-ADC3) * 20, vcc reference
  ADMUX = (15 << MUX0) | (2 << REFS0);
  // Enable ADC, 64x prescaler
  ADCSRA = _BV(ADEN) | (6 << ADPS0);
  // ADC3 is pulled at ~2.5v
  ADCSRB = 0;
  // start conversion
  ADCSRA  |= _BV(ADSC);
//  pinMode(1, OUTPUT);
  mySerial.begin(2400);
  mySerial.println("Starting...");
}

void loop()
{
  uint16_t reading = 0;
  // Has the conversion finished?
  if ((ADCSRA & _BV(ADSC)) == 0) {
    reading = ADCL + (ADCH << 8);
    sum -= samples[index];
    sum += reading;
    samples[index++] = reading;
    if (index == NUM_SAMPLES) {
      index = 0;
    }
    mySerial.println(sum / NUM_SAMPLES);
    ADCSRA  |= _BV(ADSC);
  }
}
