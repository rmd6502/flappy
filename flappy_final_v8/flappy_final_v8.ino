//#include <SoftwareSerial.h>
#include <Servo.h> 
#include "pitches.h"

#define BOX_OPEN 90
#define BOX_CLOSE 0

#define CHARACTER_BOTTOM 40
#define CHARACTER_TOP 85

const int magnetPin = 1;     // the number of the reed switch
const int buttonPin = 0;  // the number of the pushbutton pin for bird
const int ledPin =  3;      // the number of the LED pin
int magnetState = 0;         // variable
int buttonState = 0;         // variable 
int birdup = CHARACTER_BOTTOM; //start 
boolean released = true;  
boolean in_game =false;
Servo myservoRoll;
Servo myservoBird;
Servo myservoGame;

int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};// notes in the melody:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 }; // note durations: 4 = quarter note, 8 = eighth note, etc.:

int jumpmusic[] = {
  NOTE_A3};// notes in the melody:
int jumpDurations[] = {
  4}; // note durations: 4 = quarter note, 8 = eighth note, etc.:

//SoftwareSerial mySerial(4,2);
void setup() 
{ 
  //mySerial.begin(9600); //setup usb communication

  myservoBird.attach(6);
  myservoRoll.attach(5);
  myservoGame.attach(8);
  myservoGame.write(BOX_CLOSE); 
  pinMode(magnetPin, INPUT);  //reed
  pinMode(buttonPin, INPUT_PULLUP); //button 
  pinMode(ledPin, OUTPUT);   
  digitalWrite(magnetPin, HIGH);   //internal pullup
} 

void loop() {
  magnetState = digitalRead(magnetPin);
  buttonState = digitalRead(buttonPin);

  //start game 
  if (buttonState == LOW && in_game==false){
    myservoGame.write(BOX_OPEN); //open box
    birdup=CHARACTER_BOTTOM; //bird position
    delay (700);
    myservoRoll.write(60); //roll background

    in_game=true;
  }
  if(in_game==true)
  {
    if ((buttonState == LOW) && released ==true)
    {
      released = false;    
      if(birdup > 10){
        birdup-=10; //going up

      }
      for (int thisNote = 0; thisNote < 1; thisNote++) {
        int jumpDuration = 1000/jumpDurations[thisNote];
        tone(8, jumpmusic[thisNote],jumpDuration);
        int pauseBetweenNotes = jumpDuration * 13 / 10;
        delay(pauseBetweenNotes);
        //noTone(1);
      }
    }
    else
    {
      if(birdup < CHARACTER_TOP){
        birdup+=1; //going up
        delay(10);
      }
    }
    if(buttonState == HIGH)
    {
      released = true;
    }

    myservoBird.write(birdup);
    delay (50);

    //mySerial.println(birdup);
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
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 13 / 10;
    delay(pauseBetweenNotes);
    //noTone(8);
  }
}






