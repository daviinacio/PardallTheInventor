#include "HCPS.h"

HCPS::HCPS(int switchPin){
	//this->buttonPin = buttonPin;
	this->switchPin = switchPin;
	// PinMode board
	//pinMode(this->buttonPin, INPUT);
	pinMode(this->switchPin, OUTPUT);
	// Initialize board
	digitalWrite(this->switchPin, HIGH);
}

void HCPS::shutdown(){
	digitalWrite(this->switchPin, LOW);
}
