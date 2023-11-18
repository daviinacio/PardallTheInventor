#ifndef CI01_h
#define CI01_h

#include "Define.h"
#include <Arduino.h>

#include <PortExpander_I2C.h>
#include <Thread.h>

#include "Utility/AIP.h"
#include "Utility/AOF.h"
#include "Utility/State.h"
#include "Utility/MiniThread.h"

#define CI01_DEFAULT_SETA_INTERVAL		500
#define CI01_DEFAULT_I2C 				0x21

#define F_AUTO 110

#define SETA_D 'd'
#define SETA_E 'e'
#define SETA_A 'a'
#define SETA_O 'o'

#define CLED_D '0'
#define CLED_L '1'
#define CLED_B 'b'

class CI01 {
	public:
		// Constructor
		CI01();
		CI01(int, int);						// LDR, Farol							//
		CI01(int, int, int);				// LDR, Farol, Interval					//
		CI01(int, int, int, int);			// LDR, Farol, Interval, i2cPort		//
		
		// Setter
		void setSetaInterval(int);			//										//
		void setFarol(int);					//										//
		void setLDR(int);					//										//
		void setI2C(int);					//										//
		
		// Functions
		void init();						// Initialize the i2c					//
		void run();							// Update the output value				//
		
		// Interface
		AIP ldr;
		AOF farol;
		State seta;
		State freio;
		State re;
		
		State cled;
		
		bool isLit;
	private:
		PortExpander_I2C i2c;
		MiniThread setaThread, cledThread;
		
		void thread_seta_function();
		void thread_cled_function();
		void contructor(int, int, int, int);
};

#endif
