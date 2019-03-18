#include <Servo.h> // servo library

Servo rightmotor; // Servo object
Servo leftmotor; // Servo object


const int d = 24;
const int f = 57;
int t = 0;

void setup() {
  // put your setup code here, to run once:
    leftmotor.attach(11, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
    rightmotor.attach(10, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
}

void loop() {
  // put your main code here, to run repeatedly:
 while (t<4){
 straight(d, f);
 delay(1000);
 turn90();
 delay(500);
 t++;
 
 }
 
 exit(0);
}

void turn90(){
        rightmotor.write(135);    
        leftmotor.write(135);
        delay(420);
        rightmotor.write(90);    
        leftmotor.write(90);  
       }

void straight(int d, int f){
        rightmotor.write(150);    
        leftmotor.write(30);
        delay(f*d);
        rightmotor.write(90);    
        leftmotor.write(90);  
       }
       
