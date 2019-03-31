// line following code made by Lab Group 3 for RBE 1001.

#include <Servo.h> // use servo library

Servo rightmotor;   // declare servo object
Servo leftmotor;    // declare servo object

//***Start of setup***

int leftMotorPin = 10;        // pin used to interface with the LEFT motor
int rightMotorPin = 11;       // pin used to interface with the RIGHT motor
int inputPin = 2;             // digital pin number to read sensor input from
int velocity = 70;            // constant that determines speed, value from 0 to 90
int jerk = 20;                // constant that determines how agressive the robot will react to line changes, values from 0 to 100, higher values mean more agressive correction
int refresh = 100;            // delays loop by input in milliseconds
bool highWhenOnLine = true;   // whether the sensor is in an ON state when sensing the BLACK line
bool outsideFollow = true;    // if the robot will should the line on the outside enter TRUE, enter FALSE if the robot should follow the inside
bool clockwiseFollow = true;  // if the robot will should the line clockwise enter TRUE, enter FALSE for anticlockwise motion

//***End of setup***

// variables used
int slowerVelocity; // what speed the motors need to run at to correct onto the line
bool onLine;        // whether or not the robot is on the line, TRUE when sensing line
bool correctLeft;   // which direction will yield motion AWAY from the line, TRUE if leftwards motion steers the robot away from the line

void setup() {                // setup code, runs once
  Serial.begin(9600);         // initialize serial communication at 9600 bits per second
  leftmotor.attach(leftMotorPin, 1000, 2000);     // left drive motor pin number, pulse time for 0,pulse time for 180
  rightmotor.attach(rightMotorPin, 1000, 2000);   // right drive motor pin number, pulse time for 0, pulse time for 180
  pinMode(inputPin, INPUT);   // make the input pin for the sensor an input
 
  calcCorrectTurn;    // inital calculation of which direction will yield motion AWAY from the line, only needs to be run once
  calcSlowerVelocity; // inital calculation of what speed the motors need to run at to correct onto the line, only needs to be run once
 
  delay(3000); // grace period before robot starts
}

void loop() { // main code, runs repeatedly
  calcLocation;     // determine whether or not the robot is sensing the line
  drive;            // correct by veering left or right based on previous result
  delay(refresh);   // optional delay in loop, thus delaying sensing and correction
}

int calcLocation(int inputPin, bool highWhenOnLine){  // determine whether or not the robot is sensing the line
  if (((digitalRead(inputPin) == HIGH) && (highWhenOnLine == true)) || ((digitalRead(inputPin) == LOW) && (highWhenOnLine == false))){ //boolean XOR function
    // determined that the robot is sensing line
    Serial.println("On Line"); // print robot status to serial port
    onLine = true;             // set variable to refelect current robot status
  }
   else{
    // determined that the robot is not sensing line
    Serial.println("Off Line"); // print robot status to serial port
    onLine = false;             // set variable to refelect current robot status
  }            
  return onLine;  // return variable
}

int calcCorrectTurn(bool outside, bool clockwise){  // calculation of which direction will yield motion AWAY from the line
  if (((outsideFollow = true) && (clockwiseFollow = true)) || ((outsideFollow = false) && (clockwiseFollow = false))){ //boolean XOR function
    // determined that the robot has to turn left to steer away from line
    correctLeft = true; // set variable to refelect current robot status 
  }
  else{
     // determined that the robot has to turn left to steer away from line
    correctLeft = false; // set variable to refelect current robot status 
  }
  return correctLeft; // return variable
}

int calcSlowerVelocity(int velocity, int jerk){ // calculation of what speed the motors need to run at to correct onto the line
  slowerVelocity = velocity * (jerk/100); // calculate alternative speed using jerk input
  slowerVelocity = constrain(slowerVelocity, 0 , 90); // ensure alternative speed falls within usable range
  return slowerVelocity;  // return variable
}

void drive(int velocity, int slowerVelocity, bool onLine, bool correctLeft){ // robot corrects by veering left or right based on input
  if (((onLine = true) && (correctLeft = true)) || ((onLine = false) && (clockwiseFollow = false))){ //boolean XOR function
    // correcting by steering to the left, left motor has to be slowed down
    leftmotor.write(90+slowerVelocity); // slow down left motor
    rightmotor.write(90-velocity);      // run right motor at normal speed
    Serial.println("Correcting Left");  // print correction direction to serial port
  }
  else{
    // correcting by steering to the right, right motor has to be slowed down
    leftmotor.write(90+velocity);        // run left motor at normal speed
    rightmotor.write(90-slowerVelocity); // slow right left motor
    Serial.println("Correcting Right");  // print correction direction to serial port
  }
} 
  
  

  
  



