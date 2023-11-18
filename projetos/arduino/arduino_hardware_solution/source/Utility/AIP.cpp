#include "AIP.h"

AIP::AIP(){
	
}

AIP::AIP(int port){
	this->port = port;
	pinMode(this->port, INPUT);
	this->setBufferLength(10);
}

AIP::AIP(int port, int bufferLength){
	this->port = port;
	this->setBufferLength(bufferLength);
	pinMode(this->port, INPUT);
}

void AIP::setBufferLength(int bufferLength){
	this->bufferLength = bufferLength;
	
	this->buffer = new int[bufferLength];
	
	this->clearBuffer();
}

void AIP::run(){
	int read = this->read();
	this->incrementBuffer(read);
}

int AIP::read(){
	return analogRead(this->port);
}

int AIP::get(){
	return get(255);
}

int AIP::get(int max){
	int values = 0, count = 0;
	
	for(int i = 0; i < bufferLength; i++){
		if(buffer[i] == ARRAY_NULL) continue;	// Ignore NULL buffer value
		values += buffer[i]; count++;			// Increment values and count
	}
	
	int middle = values / count;				// Make middle
	return map(middle, 0, 1023, 0, max);		// Convert 0 ~ 1024 to 0 ~ max
}

void AIP::clearBuffer(){
	for(int i = 0; i < this->bufferLength; i++)
		this->buffer[i] = ARRAY_NULL;
}

void AIP::incrementBuffer(int value){
	for(int i = bufferLength - 1; i > 0; i--)
		buffer[i] = buffer[i - 1];
	buffer[0] = value;
}

