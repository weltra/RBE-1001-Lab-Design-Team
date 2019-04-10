#include "Arduino.h"
#include <Servo.h> // servo library
#include <EEPROM.h>

Servo rightmotor; // Servo object
Servo leftmotor; // Servo object
Servo armmotor; // Servo object

const int leftMotorPin = 4; // Motor pin number that interfaces with the left motor
const int rightMotorPin = 5; // Motor pin number that interfaces with the right motor
const int armMotorPin = 6; // Motor pin number that interfaces with the arm motor
const int leftInputPin = 22; // Digital pin number that receives input from the left photosensor
const int rightInputPin = 23; // Digital pin number that receives input from the right photosensor
const int potInputPin = 11; // Analog pin number that receives input from the potentiometer
const int propError = 1; //This is the proportional constant

const int turnDelay = 60;
const int x = 15;
const int y = 20;
//The setup function is called once at startup of the sketch
void setup()
{
  // Add your initialization code here
  Serial.begin(9600); // start serial output at 9600
  leftmotor.attach(leftMotorPin, 1000, 2000); // set up left motor
  rightmotor.attach(rightMotorPin, 1000, 2000); // set up right motor
  armmotor.attach(armMotorPin, 1000, 2000); // set up arm motor
  pinMode(leftInputPin, INPUT); // set up input pin that receives input from the left photosensor
  pinMode(rightInputPin, INPUT); // set up input pin that receives input from the right photosensor
  pinMode(potInputPin, INPUT); // set up input pin that receives input from the potentiometer
  delay(1000); // grace period after startup (in ms)
}

// The loop function is called in an endless loop
void loop()
{
  int armdelay = 100;
  int armspeed = 10;
  //the values are for deadreckoninig the arm, because portion control sucks and the potentiometer is annoying

  armmotor.write(90 - armspeed);
  delay(armdelay);
  drive(25);
  int leftPhoto = digitalRead(22);
  int rightPhoto = digitalRead(23);

  //for left side/right turn
  if (leftPhoto == LOW && rightPhoto == HIGH) {
    rightmotor.write(90 - y);
    leftmotor.write(90 - x);
    delay(turnDelay);
  }

  //for right side/left turn
  if (leftPhoto == HIGH && rightPhoto == LOW) {
    rightmotor.write(90 + x);
    leftmotor.write(90 + y);
    delay(turnDelay);
  }

  //for first horizontal line
  if (leftPhoto == LOW && rightPhoto == LOW) {
    rightmotor.write(90);
    leftmotor.write(90);
    armmotor.write(90 + armspeed);
    delay(armdelay);

    //this is a janky solution to getting it to keep going, that first turn might need some deadreckoning, but it definetly needs to move forward a bit before this so it doesnt read the same line twice

    //left sensor
    if (leftPhoto == LOW && rightPhoto == HIGH) {
      rightmotor.write(90 - y);
      leftmotor.write(90 - x);
      delay(turnDelay);
    }

    /right sensor
    if (leftPhoto == HIGH && rightPhoto == LOW) {
      rightmotor.write(90 + x);
      leftmotor.write(90 + y);
      delay(turnDelay);
    }

    //second line full stop, just pick it up before 30 sec, if it gets false positives before line have it lower the arm instead so it gets closer and closer and then lifts the back wheels off on the final line 
    if (leftPhoto == LOW && rightPhoto == LOW) {
      rightmotor.write(90);
      leftmotor.write(90);
      delay(30000);
    }
  }
}

//void drive(int speed, int direction){
//  leftmotor.write(constrain(90-speed+direction,0,180));
//  rightmotor.write(constrain(90+speed+direction,0,180));
//}

void drive (int speed) {
  leftmotor.write (90 + speed);
  rightmotor.write (90 - speed);
}



void armMotor(int pin, int desiredVal) {

  const float r = 0.1; // higher values make for more agressive
  float x;

  int difference = desiredVal - analogRead(pin);

  while (abs(difference) < 5) {
    x = 90 + difference * r;
    armmotor.write(constrain(x, 0, 180));

    difference = desiredVal - analogRead(pin);
  }
}
