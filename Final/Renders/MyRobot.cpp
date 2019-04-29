#include "MyRobot.h"
#include "Arduino.h"


Servo rightmotor;   // declare servo object
Servo leftmotor;    // declare servo object
Servo grasperMotor;
Servo armmotor;

const int leftMotorPin = 10;        // pin used to interface with the LEFT motor
const int rightMotorPin = 11;       // pin used to interface with the RIGHT motor
const int armmotorPin = 6;             
const int grasperMotorPin= 4; 

int state = 0;
int potPin=1; //go back and check to make sure this number is an analog pin
int potVariable;
int desiredValue=600; //this is the potentiometer value for the arm at the second floor
int bumpSwitch=28; //go back to make sure this number is a digital pin
int bump = 0; //this means the bump switch is not pushed
bool downButton;
bool upButton;
bool fourButton;
bool twoButton;
int ledPin= 24; //make sure that is a digital pin
/**
 * Called when the start button is pressed and the robot control begins
 */
 void MyRobot::robotStartup(){
		//Serial.println("Here is where I start up my robot code");
    Serial.begin(9600);         // initialize serial communication at 9600 bits per second
  leftmotor.attach(leftMotorPin, 1000, 2000);     // left drive motor pin number, pulse time for 0,pulse time for 180
  rightmotor.attach(rightMotorPin, 1000, 2000);   // right drive motor pin number, pulse time for 0, pulse time for 180
  armmotor.attach(armmotorPin, 1000,2000); //arm motor pin number
  grasperMotor.attach(grasperMotorPin, 1000, 2000); // right drive motor pin#, pulse time for 0,pulse time for 180
  pinMode(potPin, INPUT);           // set pin to input
  pinMode(bumpSwitch, INPUT_PULLUP); 
  pinMode (ledPin, OUTPUT);
  state = 0;
 }
/**
 * Called by the controller between communication with the wireless controller
 * during autonomous mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
void MyRobot::turnBot(){
  leftmotor.write(60);
  rightmotor.write(60);
}
void MyRobot::armRaise() {   
    armmotor.write(45);
  }
void MyRobot:: armLower(){
    armmotor.write(135);
}
void MyRobot::armDrop() {
    armmotor.write(120);
} 
void MyRobot::driveForward() {
    leftmotor.write(120);
    rightmotor.write(60);   
  }
void MyRobot::driveBackward(){
    leftmotor.write (60);
    rightmotor.write (120);
}
void MyRobot::stopMotor(){
  leftmotor.write(90);
  rightmotor.write(90);
}
void MyRobot::grasperRelease(){
  grasperMotor.write(180);
}
void MyRobot :: grasperIntake(){
  grasperMotor.write (0);
}
void MyRobot :: grasperStop(){
  grasperMotor.write(90);
}
void MyRobot::armStop(){
  armmotor.write(90);
}
void MyRobot::autonomous( long time){

   bump=digitalRead(bumpSwitch);
   //Serial.println(digitalRead(bumpSwitch)); 
   potVariable=analogRead(potPin);
   Serial.println(potVariable);
   Serial.println(state);
   if (bump==LOW){
    digitalWrite(ledPin, HIGH);
   }
   else if (bump==HIGH){
    digitalWrite(ledPin,LOW);
   }
   switch (state) {
  case 0: //raise arm
   // Serial.println(potVariable);
    if (potVariable < desiredValue){
      MyRobot::armDrop();
    }
    else if (potVariable > desiredValue){
      MyRobot::armRaise();
    }
    else if(potVariable < (desiredValue + 50) || potVariable > (desiredValue - 50)){
    MyRobot::armStop();
    state=1;
    }
    break;
  case 1: //drive forward
    MyRobot:: driveForward();
    delay(5200);
    MyRobot::stopMotor();
    state=2;
   break;
  case 2:
   MyRobot::turnBot();
   delay(1100);
   MyRobot::stopMotor();
   state=3;
   break;
  case 3: //drive forward
    MyRobot::driveForward();
    //Serial.println(digitalRead(bumpSwitch));
    if(bump==LOW){
    state=4;
    }
    break;
  case 4: //stop robot
    MyRobot::stopMotor();
    state=5;
    break;
  case 5: //reverse robot
    MyRobot:: driveBackward();
    delay (1100);
    MyRobot::stopMotor();
    state=6;
    break;
   case 6: //lower arm
    MyRobot::armLower();
    delay(400);
    MyRobot:: armStop();
    state=7;
    break;
   case 7: //drive forward
    MyRobot:: driveForward();
    delay(1000);
    state=9;
     break;
   case 9: //stop robot
    MyRobot::stopMotor();
    state=10;
    break;
  case 10: //release pizza
    MyRobot::grasperRelease();
    delay(3000);
    MyRobot::armStop();
    state=11;
    break;
  case 11:
   leftmotor.write(90);
   rightmotor.write(90);
   state= 12;
   break;
  default:
    // statements
    break;
}
 }
/**
 * Called by the controller between communication with the wireless controller
 * during teleop mode
 * @param time the amount of time remaining
 * @param dfw instance of the DFW controller
 */
 void MyRobot::teleop( long time){
//		Serial.print("\r\nTeleop time remaining: ");
//		Serial.print(time);
//		Serial.print("\tright joystick: ");
//		Serial.print(dfw->joystickrv());
//		Serial.print("\tleft joystick: ");
//		Serial.print(dfw->joysticklv());
      rightmotor.write(180-dfw->joystickrv());     //DFW.joystick will return 0-180 as an int into rightmotor.write
      leftmotor.write(dfw->joysticklv());      //DFW.joystick will return 0-180 as an int into leftmotor.write
    upButton= dfw->up(); //double check to make sure buttonUp is the correct command
    downButton= dfw->down(); //double check to make sure buttonDown is the correct comand
    fourButton = dfw->four(); //double check to make sure buttonRelease is the correct command
    twoButton = dfw->two(); //double check to make sure buttonCollect is the correct command
   if(upButton==true && downButton==false){
    armRaise();
   }
   else if(upButton==false && downButton==true){
    armDrop();
   }
   else if (upButton==false && downButton==false){
    armStop();
   }
   if (fourButton==true && twoButton==false){
    grasperRelease();
   }
   else if (twoButton==true && fourButton==false){
    grasperIntake();
  }
    else if (fourButton==false && twoButton==false){
      grasperStop();
    }
 }
/**
 * Called at the end of control to reset the objects for the next start
 */
 void MyRobot::robotShutdown(void){
		//Serial.println("Here is where I shut down my robot code");

 }
