#include <SoftwareSerial.h>
#include <Servo.h>

static const uint8_t analog1 = 2;
static const uint8_t analog2 = 5;

SoftwareSerial mySerial(4,0);
Servo rollingServo;

#define NUM_SAMPLES 64
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
  
  DIDR0 = _BV(ADC1D) | _BV(ADC3D);
//  pinMode(1, OUTPUT);
  rollingServo.attach(6);
  mySerial.begin(9600);
  mySerial.println("Starting...");
}

void loop()
{
  static uint16_t last = 0;
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
    uint16_t average = sum/NUM_SAMPLES;
    int16_t delta = average - last;
    last = average;
    rollingServo.write(map(average, 275,330, 45,135));
    mySerial.print(average);mySerial.print("  ");mySerial.println(delta);
    ADCSRA  |= _BV(ADSC);
  }
}
