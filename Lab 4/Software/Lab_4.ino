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
const int potInputPin = 24; // Analog pin number that receives input from the potentiometer

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

//Add your repeated code here
}

void drive(int speed, int direction){
	leftmotor.write(constrain(90-speed+direction,0,180));
	rightmotor.write(constrain(90+speed+direction,0,180));
}

void armMotor(int pin, int desiredVal){

	const float r = 0.1; // higher values make for more agressive

	int difference;
	float x;

	difference = desiredVal-analogRead(pin);

	while(abs(difference) < 5){
		x = 90+difference*r;
		armmotor.write(constrain(x,0,180));

		difference = desiredVal-analogRead(pin);
	}
}
