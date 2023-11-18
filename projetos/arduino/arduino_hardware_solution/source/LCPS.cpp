#include "LCPS.h"

LCPS::LCPS(int switchPin){
	this->switchPin = switchPin;
	// PinMode board
	pinMode(this->switchPin, OUTPUT);
	// Initialize board
	digitalWrite(this->switchPin, HIGH);
}

void LCPS::shutdown(){
	digitalWrite(this->switchPin, LOW);
}
