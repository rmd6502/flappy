#include <Servo.h> 
#include "pitches.h"
const int magnetPin = 1;     // the number of the reed switch
const int tapPin = 0;        // the number of the pushbutton pin for bird
const int carPin = 2;        // the number of the pushbutton pin for the car
const int ledPin =  3;      // the number of the LED pin
int magnetState = 0;         // variable
int tapState = 0;         // variable 
int carState = 0;         // variable 
int location = 40; //start 
boolean released = true;  
boolean in_tap_game =false;
boolean in_car_game =false;
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

void setup() 
{ 
  myservoBird.attach(6);
  myservoRoll.attach(5);
  myservoGame.attach(8);
  myservoGame.write(0); 
  pinMode(magnetPin, INPUT);  //reed
  pinMode(tapPin, INPUT);
  pinMode(carPin, INPUT);
  pinMode(ledPin, OUTPUT);   
  digitalWrite(magnetPin, HIGH);   //internal pullup
} 

void loop() {
  magnetState = digitalRead(magnetPin);
  tapState = digitalRead(tapPin);
  carState = digitalRead(carPin);

  //start game 
  if (tapState == HIGH && in_tap_game==false && in_car_game==false){
    myservoGame.write(85); //open box
    location=40; //bird position
    delay (700);
    myservoRoll.write(60); //roll background

    in_tap_game=true;
  }
  if(in_tap_game==true)
  {
    if ((tapState == HIGH) && released ==true)
    {
      released = false;    
      if(location > 10){
        location-=10; //going up

      }
      for (int thisNote = 0; thisNote < 1; thisNote++) {
        int jumpDuration = 1000/jumpDurations[thisNote];
        tone(8, jumpmusic[thisNote],jumpDuration);
        int pauseBetweenNotes = jumpDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(1);
      }
    }
    else
    {
      if(location < 85){
        location+=1; //going up
        delay(10);
      }
    }
    if(tapState == LOW)
    {
      released = true;
    }

    myservoBird.write(location);
    delay (50);

    //game over; when bird hits ground
    if (location >84)
    {
      game_over();
    }
    //game over: when bird hit pipes
    if (magnetState == LOW) 
    {    
      game_over();
    }
  }
  
  
  
  //start   CAR game 
  if (carState == HIGH && in_tap_game==false && in_car_game==false){
    myservoGame.write(85); //open box
    location=40; //bird position
    delay (700);
    myservoRoll.write(60); //roll background

    in_car_game=true;
  }
  if(in_car_game==true)
  {
    if (tapState == HIGH)
    {
      location+=3;
    }
    if (carState == HIGH)
    {
      location-=3;
    }
    myservoBird.write(location);
    delay (50);

    //game over; when bird hits ground
    if (location >84 || location<0)
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
  in_car_game =false;
  in_tap_game =false;
  location = 40;
  released = true;
  myservoRoll.write(90); //stop roll background
  myservoGame.write(0); //close game box
  myservoBird.write(location);//bird go back to position 40
  digitalWrite(ledPin, HIGH);
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}






