#include "Arduino.h"
#include <EEPROM.h>

const int potInputPin = 24;
const int firstAngle = 0;
const int secondAngle = 90;

int ratio; // pot value change per angle change

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	pinMode(potInputPin, INPUT);

}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	int firstVal;
	int secondVal;

	firstVal = record(potInputPin, firstAngle);
	secondVal = record(potInputPin, secondAngle);

	ratio = (secondVal-firstVal)/(secondAngle-firstAngle);
	Serial.print("Ratio equals-");
	Serial.println(ratio);


	EEPROMwrite(ratio);
	EEPROMwrite(firstAngle);

	exit(0);
}

int record(int pin, int angle){
	int val;

	Serial.print("Please move robot arm up-");
	Serial.print(angle);
	Serial.println("-degrees from the zero position");
	delay(5000);

	val = analogRead(pin);
	Serial.print("Value recorded,-");
	Serial.print(angle);
	Serial.print("-degrees equals analog value of-");
	Serial.println(val);

	return val;
}

void EEPROMwrite(int var){
	int addr = 0;
	int val  = var / 4;

	EEPROM.write(addr, val);
	addr = addr + 1;
	if (addr == EEPROM.length()) {
    addr = 0;
    Serial.print("Stored to byte-");
	Serial.print(addr);
	Serial.print("-in EEPROM");
    delay(100);
  }

}

