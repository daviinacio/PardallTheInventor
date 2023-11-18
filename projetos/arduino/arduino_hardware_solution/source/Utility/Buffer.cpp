#include "Buffer.h"

//Buffer::Buffer(){this->nu }

Buffer::Buffer(int bufferLength){
	this->setLength(bufferLength);
	this->null_var = -1;
}

Buffer::Buffer(int bufferLength, int null_var){
	this->setLength(bufferLength);
	this->null_var = null_var;
}

char Buffer::get(int i){
	return this->buffer[i];
}

void Buffer::setLength(int bufferLength){
	this->bufferLength = bufferLength;
	
	this->buffer = new char[bufferLength];
	
	this->clear();
}

void Buffer::clear(){
	this->clear(null_var);
}

void Buffer::clear(char char_null){
	for(int i = 0; i < this->bufferLength; i++)
		this->buffer[i] = char_null;
}

void Buffer::increment(char value){
	for(int i = this->bufferLength - 1; i > 0; i--)
		buffer[i] = buffer[i - 1];
	buffer[0] = value;
}
