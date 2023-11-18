#ifndef HCPS_h
#define HCPS_h

#include "Define.h"
#include <Arduino.h>

class HCPS {
	public:
		HCPS(int);
		//HCPS(int, int);
		void shutdown();
	private:
		int switchPin;
		//int buttonPin, switchPin;
};

#endif
