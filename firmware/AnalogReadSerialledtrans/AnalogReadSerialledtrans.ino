/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

static const int led = A5;
static const int sensor = A0;

static const int NUM_SAMPLES = 16;
static uint16_t onValues[NUM_SAMPLES] = {0};
static uint32_t onSum = 0L;
static uint8_t onIndex = 0;
static uint16_t offValues[NUM_SAMPLES] = {0};
static uint32_t offSum = 0L;
static uint8_t offIndex = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  static uint32_t inittime = millis();
  // read the input on analog pin 0:
  int sensorValue = analogRead(sensor);
  
  if (digitalRead(led)) {
    onSum += sensorValue;
    onSum -= onValues[onIndex];
    onValues[onIndex] = sensorValue;
    onIndex = (onIndex + 1) % NUM_SAMPLES;
  } else {
    offSum += sensorValue;
    offSum -= offValues[offIndex];
    offValues[offIndex] = sensorValue;
    offIndex = (offIndex + 1) % NUM_SAMPLES;
  }
  // print out the value you read:
  Serial.println(offSum/NUM_SAMPLES - onSum/NUM_SAMPLES);
  delay(1);        // delay in between reads for stability
  if (millis() - inittime > 25) {
    digitalWrite(led, HIGH);
  }
    if (millis() - inittime > 50) {
    digitalWrite(led, LOW);
    inittime = millis();
  }
}
