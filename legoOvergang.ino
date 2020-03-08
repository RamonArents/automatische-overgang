/*
 * Name: Lego Railroad Crossing
 * Author: Ramon Arents
 * Date: 8-3-2020 
 */

//include required libraries
#include <NewPing.h>
#include <Servo.h>
//constants, to define the pings and max distance
#define TRIG_PIN 12
#define ECHO_PIN 13
#define MAX_DISTANCE 500
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); //NewPing library configuration
// LED pins
int redLed1 = 3;
int redLed2 = 2;
//configure servos
Servo myServo;
Servo myServo2;

void setup() {
  //set the LEDS and the TRIG_PINT on output. Set the ECHO_PIN on input.
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  //attach servo motors on pin 8 and 9
  myServo.attach(8);
  myServo2.attach(9);
}

void loop() {
  //Standard configuration when nothing happens for the distance sensor
  int duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH); // echo receives ping
  distance = (duration / 2) / 29.1; 
  //when sensor detects objects within 10 cm
  if(distance <= 10){
    // put the crossing guards down
    myServo.write(90);
    myServo2.write(180);
    // blink LEDS
    blinkLeds(7, 200);   
 }else{
    //wait till the train has passed
    delay(900);
    //put the crossing guards back up
    myServo.write(180);
    myServo2.write(90);
  }
  delay(450);
}

/*
 * Function to blink the LED
 * @return void
 */
void blinkLeds(int blinkTimes, int blinkDelay){
  //blink LEDS during close
  int i = 0;
  // loop and blink LEDS during closing
  for(i = 0; i  <= blinkTimes; i += 1){
    digitalWrite(redLed1, HIGH);
    digitalWrite(redLed2, LOW);
    delay(blinkDelay);
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, HIGH);
    delay(blinkDelay);
  }
  // turn the LEDS off at the end
  digitalWrite(redLed1, LOW);
  digitalWrite(redLed2, LOW);
}
