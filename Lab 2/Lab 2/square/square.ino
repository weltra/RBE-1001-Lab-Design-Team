#include <Servo.h> // servo library

Servo rightmotor; // Servo object
Servo leftmotor; // Servo object

const int l; //length of side of square

int t; //declare count variable
float d; //declare distance variable
float c = 2455; //declare distance conversion constant
const float v = 50; //declare motor speed


void setup() {
  // put your setup code here, to run once:
    leftmotor.attach(11, 1000, 2000); // left drive motor pin#, pulse time for 0,pulse time for 180
    rightmotor.attach(10, 1000, 2000); // right drive motor pin#, pulse time for 0, pulse time for 180
delay(3000); //grace period before robot starts moving
}

void loop() {
  // put your main code here, to run repeatedly:
  square(24); //make square
  exit(0); //stop program
}

void driveStraight(float d, float c){
        rightmotor.write(90-v); 
        leftmotor.write(90+v); //start motors
        delay(c*(d/v)); //wait for time calculated using distance conversion constant.
        rightmotor.write(90);
        leftmotor.write(90); //stop motors
}   
    
void turn90(){
        rightmotor.write(135); //initiate turn by starting motors 
        leftmotor.write(135);
        delay(570); //wait for time
        rightmotor.write(90);  
        leftmotor.write(90); //stop motors
}   
         
          
void square(int l){
        while (t<4){ //run following code as long as there are less than 4 sides drawn
          driveStraight(l,c); //make a line
          delay(500);
          turn90(); //turn to prepare for the next line
          delay(500);
          t++; //add to sides drawn
        }
}


  

