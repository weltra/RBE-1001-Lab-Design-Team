#include <Servo.h> // servo library

Servo rightmotor; // Servo object
Servo leftmotor; // Servo object

const int t = 2000; //ms

void setup() {
  // put your setup code here, to run once:
    leftmotor.attach(4, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
    rightmotor.attach(11, 1000, 2000); // right drive motor pin#, pulse time for 0, pulse time for 180
delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  rightmotor.write(180); 
  leftmotor.write(0);
  
  delay(t/2);
  
  rightmotor.write(0); 
  leftmotor.write(180);
  
  delay(t/2);
}
       
       
