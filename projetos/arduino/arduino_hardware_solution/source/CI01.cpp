#include "CI01.h"

#define SETA_D_PORT 3
#define SETA_E_PORT 2
#define FREIO_LOW_PORT 1
#define FREIO_HIGH_PORT 0
#define RE_PORT 4
#define CLED_PORT 5

#define SETA_VALID_VALUE(v) (v == SETA_D || v == SETA_E || v == SETA_A || v == SETA_O)

#define LDR_CLARO 200
#define LDR_ESCURO 50

// Constructor
CI01::CI01(){
	
}

CI01::CI01(int ldr, int farol){
	this->contructor(ldr, farol, CI01_DEFAULT_SETA_INTERVAL, CI01_DEFAULT_I2C);
}

CI01::CI01(int ldr, int farol, int interval){
	this->contructor(ldr, farol, interval, CI01_DEFAULT_I2C);
}

CI01::CI01(int ldr, int farol, int interval, int i2c_port){
	this->contructor(ldr, farol, interval, i2c_port);
}

void CI01::contructor(int ldr, int farol, int interval, int i2c_port){
	this->setLDR(ldr); this->farol = AOF(farol, interval); this->setSetaInterval(interval / 2); this->setI2C(i2c_port);
	
	this->cledThread = MiniThread(interval / 4);
	
	this->farol.setPWM(0);
	this->freio.set(LOW);
}

// Setter
void CI01::setSetaInterval(int interval){
	this->setaThread = MiniThread(interval);
}

void CI01::setFarol(int farol){
	this->farol = AOF(farol);
}

void CI01::setLDR(int ldr){
	this->ldr = AIP(ldr);
}

void CI01::setI2C(int i2c){
	this->i2c = PortExpander_I2C(i2c);
}

// Function
void CI01::init(){
	this->i2c.init(0xff);
	//this->i2c.digitalWriteAll(HIGH);						// Clear the i2c
	i2c.digitalWrite(FREIO_LOW_PORT, LOW);
}

void CI01::run(){
	this->ldr.run();
	this->farol.run();
	
	// Check if is bright
	if(ldr.get(1023) > LDR_CLARO)	this->isLit = true; else
	if(ldr.get(1023) < LDR_ESCURO)	this->isLit = false;
	
	// Light dependent compenent
	this->i2c.digitalWrite(FREIO_LOW_PORT, this->isLit);
	this->i2c.digitalWrite(RE_PORT, !this->re.get());
	
	// Sync HardWare
	this->i2c.digitalWrite(FREIO_HIGH_PORT, !this->freio.get());
	
	// Threads
	if(this->setaThread.isFinished()){
		this->thread_seta_function();
		this->setaThread.reset();
	} else
	if(this->cledThread.isFinished()){
		this->thread_cled_function();
		this->cledThread.reset();
	}
	
	// Corrections
	if(!SETA_VALID_VALUE(this->seta.get())){ 				// Avoid invalid values
		this->seta.set(SETA_O);
		Serial.println("Seta correction");
	}
}

// Thread functions
void CI01::thread_seta_function(){
	switch(this->seta.get()){
		case SETA_D:
			//if((this->i2c.digitalRead(SETA_D_PORT) == this->i2c.digitalRead(SETA_E_PORT)) != I2C_OFF)
			//	this->i2c.digitalWrite(SETA_D_PORT, I2C_OFF); else
			if(this->i2c.digitalRead(SETA_E_PORT) == I2C_OFF)	
				this->i2c.digitalWrite(SETA_D_PORT, !this->i2c.digitalRead(SETA_D_PORT));
			this->i2c.digitalWrite(SETA_E_PORT, I2C_OFF); break;
		case SETA_E:
			if(this->i2c.digitalRead(SETA_D_PORT) == I2C_OFF)
				this->i2c.digitalWrite(SETA_E_PORT, !this->i2c.digitalRead(SETA_E_PORT)); 
			this->i2c.digitalWrite(SETA_D_PORT, I2C_OFF); break;
		case SETA_A:
			//if(this->i2c.digitalRead(SETA_D_PORT) == this->i2c.digitalRead(SETA_E_PORT))
				this->i2c.digitalWrite(SETA_D_PORT, !this->i2c.digitalRead(SETA_D_PORT));
			//else this->i2c.digitalWrite(SETA_D_PORT, I2C_OFF);
			this->i2c.digitalWrite(SETA_E_PORT, this->i2c.digitalRead(SETA_D_PORT)); break;
		case SETA_O:
			this->i2c.digitalWrite(SETA_D_PORT, I2C_OFF);
			this->i2c.digitalWrite(SETA_E_PORT, I2C_OFF); break;
	}
}

void CI01::thread_cled_function(){
	switch(this->cled.get()){
		case CLED_D:
			this->i2c.digitalWrite(CLED_PORT, I2C_OFF);
			break;
		case CLED_L:
			this->i2c.digitalWrite(CLED_PORT, I2C_ON);
			break;
		case CLED_B:
			this->i2c.digitalWrite(CLED_PORT, !this->i2c.digitalRead(CLED_PORT));
			break;
	}
}
