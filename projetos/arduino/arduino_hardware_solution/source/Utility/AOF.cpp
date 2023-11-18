#include "AOF.h"

#define FADE_RATE 2

// Constructor
AOF::AOF(){
	this->setInterval(DEFAULT_INTERVAL);
}

AOF::AOF(int port){
	this->port = port;
	this->setInterval(DEFAULT_INTERVAL);
	 
	pinMode(this->port, OUTPUT);
}

AOF::AOF(int port, int interval){
	this->port = port;
	this->setInterval(interval);
	 
	pinMode(this->port, OUTPUT);
}

// Setter
void AOF::set(int value){
	if(this->V == value) return;
	
	this->To = millis();
	this->T  = this->To + this->dT;
	this->Vo = this->output;
	this->V  = value;
}

void AOF::setPWM(int value){
	
	if(isOutOfBorders(value))
		this->output = V;
	else
		this->output = value;
	
	analogWrite(this->port, this->output);
}

void AOF::setBreaking(int value){
	this->set(value);
	
	double dl = this->dT / (this->V - this->Vo);
	dl *= FADE_RATE;
	
	if(dl < 0) dl = -dl;
	
	if(dl < 1) dl = 1;
	
//	Serial.print("dT: ");
//	Serial.print(this->dT);
//	Serial.print(", dV: ");
//	Serial.print(this->V - this->Vo);
//	Serial.print(", Breaking delay: ");
//	Serial.println(dl);
	
	while(!this->isFinished()){
		delay(dl);
		this->run();
	}
}

void AOF::setBreaking(int value, int tempInterval){
	int interval = this->dT;
	this->setInterval(tempInterval);
	
	this->setBreaking(value);
	
	this->setInterval(interval);
}

void AOF::setInterval(int interval){
	this->dT = interval;
}
// Getter
int AOF::get(){
	return this->output;
}

int AOF::getVf(){
	return this->V;
}

bool AOF::isFinished(){
	return isOutOfBorders(this->output);
}

void AOF::run(){
	long tempo = millis();
	
	if(!isFinished()){
		//this->setPWM(map(tempo, To, T, Vo, V));		// In time
		//this->setPWM(map(tempo - To, To - To, T - To, Vo, V));		// In time
		
		this->setPWM(map(tempo - To, 0, dT, Vo, V));		// In time
		//this->setPWM((millis() - To) * (V - Vo) / (T - To) + Vo);		// In time
	
		//Serial.print("%");
		
		// For debug
//		Serial.print("$AOP(");
//		Serial.print(this->port);
//		Serial.print(").");
//		Serial.print("(");
//		Serial.print(tempo - To);
//		
//		Serial.print(", ");
//		Serial.print(0);
//		
//		Serial.print(", ");
//		Serial.print(dT);
//		
//		Serial.print(", ");
//		Serial.print(Vo);
//		
//		Serial.print(", ");
//		Serial.print(V);
//		
//		Serial.print(") - out = ");
//		Serial.println(this->output);
		// End debug
	}	
	
}

bool AOF::isOutOfBorders(int x){
	return (V - Vo) > 0 and x >= V or
	   	   (V - Vo) < 0 and x <= V;
}

//long map(long x, long in_min, long in_max, long out_min, long out_max){
//	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//}
