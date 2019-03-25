#include <Servo.h> // servo library

Servo rightmotor; // Servo object
Servo leftmotor; // Servo object


float c = 2455; //distance conversion constant
const float d = 24; //distance in inches
const float v = 50; //motor speed

void setup() {
  // put your setup code here, to run once:
    leftmotor.attach(4, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
    rightmotor.attach(5, 1000, 2000); // right drive motor pin#, pulse time for 0, pulse time for 180
delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  driveStraight(d, c);
  exit(0);
}


void driveStraight(float d, float c){
        rightmotor.write(90-v); 
        leftmotor.write(90+v); //start motors
        delay(c*(d/v)); //wait for time calculated using distance conversion constant.
        rightmotor.write(90);
        leftmotor.write(90); //stop motors
}       
       
