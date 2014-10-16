#include "flappy.h"
#include <Servo.h>

Servo myServo;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(start_button, INPUT_PULLUP);
  PUEA = _BV(start_button);
  Serial1.begin(115200);
  Serial1.println("ready");
  myServo.attach(background_servo);
}

void loop()
{
  static int last = 0;
  int reading = digitalRead(start_button);
  if (reading != last) {
    Serial1.print("Changed! New Value "); Serial1.println(reading);
    last = reading;
    delay(1);
  }
  digitalWrite(led, reading);
}
