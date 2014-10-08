#include "flappy.h"

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(hall_input, INPUT_PULLUP);
  PUEA = _BV(hall_input);
  Serial1.begin(115200);
  Serial1.println("ready");
}

void loop()
{
  static int last = 0;
  int reading = digitalRead(hall_input);
  if (reading != last) {
    Serial1.print("Changed! New Value "); Serial1.println(reading);
    last = reading;
    delay(1);
  }
  digitalWrite(led, reading);
}
