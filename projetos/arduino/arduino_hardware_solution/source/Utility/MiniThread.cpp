#include "MiniThread.h"

// Constructor
MiniThread::MiniThread(){
	
}

MiniThread::MiniThread(int interval){
	this->setInterval(interval);
}

// Setter
void MiniThread::setInterval(int interval){
	this->dT = interval;
}

// Function
bool MiniThread::isFinished(){
	return millis() >= (To + dT);
}

void MiniThread::reset(){
	To = millis();
}
