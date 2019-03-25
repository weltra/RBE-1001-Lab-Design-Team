#include <Servo.h> // servo library

Servo rightmotor; // Servo object
Servo leftmotor; // Servo object


const int a = 1;
int v = 25;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    leftmotor.attach(4, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
    rightmotor.attach(5, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
delay(3000);

}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println(v);
 if (v<90){
  forward(v);
  delay(200);
  v = v + a;
 }
 else{
 forward(180);
 }
}


void forward(int v){
        rightmotor.write(90-v);    
        leftmotor.write(90+v);
}       
       
