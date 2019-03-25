#include <Servo.h> // servo library

Servo rightmotor; // Servo object
Servo leftmotor; // Servo object


const int a = 1; //accelleration value
int v = 0; //start value for speed

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //start serial output at 9600 baud
    leftmotor.attach(11, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
    rightmotor.attach(10, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
delay(3000); //grace period

}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println(v); //print v to serial
 if (v<90){
  forward(v); //exectute drive based on value of v
  delay(200);
  v = v + a; //ramp up v by factor a
 }
 else{
 rightmotor.write(90); //when both motors at full speed, keep speed
 leftmotor.write(90);
 }
}


void forward(int v){
        rightmotor.write(v); //start motor at full speed back, ramp down as v goes up
        leftmotor.write(90+v); //start motor with no speed, ramp up as v goes up
}       
       
