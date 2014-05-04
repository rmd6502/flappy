#include <Servo.h> 
#include "pitches.h"

#define BOX_OPEN 90
#define BOX_CLOSE 0

#define CHARACTER_BOTTOM 40
#define CHARACTER_TOP 85

const uint8_t magnetPin = 1;     // the number of the reed switch
const uint8_t buttonPin = 0;  // the number of the pushbutton pin for bird
const uint8_t speakerPin = 7;
const uint8_t rollServoPin = 10;
const uint8_t characterServoPin = 9;
const uint8_t lidServoPin = 8;
const uint8_t ledPin =  2;      // the number of the LED pin

uint16_t magnetState = 0;         // variable
uint8_t buttonState = 0;         // variable 
uint8_t birdup = CHARACTER_BOTTOM; //start 
boolean released = true;  
boolean in_game =false;
Servo myservoRoll;
Servo myservoBird;
Servo myservoGame;

int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};// notes in the melody:
uint8_t noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 }; // note durations: 4 = quarter note, 8 = eighth note, etc.:

int jumpmusic[] = {
  NOTE_A3};// notes in the melody:
uint8_t jumpDurations[] = {
  4}; // note durations: 4 = quarter note, 8 = eighth note, etc.:

void setup() 
{ 
  myservoBird.attach(characterServoPin);
  myservoRoll.attach(rollServoPin);
  myservoGame.attach(lidServoPin);
  myservoGame.write(BOX_CLOSE); 
  pinMode(magnetPin, INPUT);  //reed
  pinMode(buttonPin, INPUT_PULLUP); //button 
  pinMode(ledPin, OUTPUT);
} 

void loop() {
  magnetState = analogRead(magnetPin);
  buttonState = digitalRead(buttonPin);

  //start game 
  if (buttonState == LOW && in_game==false){
    myservoGame.write(BOX_OPEN); //open box
    birdup=CHARACTER_BOTTOM; //bird position
    delay (700);
    myservoRoll.write(60); //roll background

    in_game=true;
    released = false;
  }
  if(in_game==true)
  {
    if ((buttonState == LOW) && released ==true)
    {
      released = false;    
      if(birdup > 10){
        birdup-=10; //going up

      }
      for (int thisNote = 0; thisNote < (sizeof(jumpmusic)/sizeof(jumpmusic[0])); thisNote++) {
        int jumpDuration = 1000/jumpDurations[thisNote];
        tone(speakerPin, jumpmusic[thisNote],jumpDuration);
        int pauseBetweenNotes = jumpDuration * 13 / 10;
        delay(pauseBetweenNotes);
      }
    }
    else
    {
      if(birdup < CHARACTER_TOP){
        birdup+=1; //going down
        delay(10);
      }
    }
    if(buttonState == HIGH)
    {
      released = true;
    }

    myservoBird.write(birdup);
    delay (50);

    //game over; when bird hits ground
    if (birdup >= CHARACTER_TOP)
    {
      game_over();
    }
    //game over: when bird hit pipes
    if (magnetState == LOW) 
    {    
      game_over();
    }
  }

}

void game_over(){
  //reset all the variables
  in_game =false;
  birdup = CHARACTER_BOTTOM;
  released = true;
  myservoRoll.write(90); //stop roll background
  myservoGame.write(BOX_CLOSE); //close game box
  myservoBird.write(birdup);//bird go back to position 40
  digitalWrite(ledPin, HIGH);
  for (int thisNote = 0; thisNote < (sizeof(melody)/sizeof(melody[0])); thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(speakerPin, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 13 / 10;
    delay(pauseBetweenNotes);
  }
}






