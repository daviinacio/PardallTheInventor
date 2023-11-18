#ifndef LCPS_h
#define LCPS_h

#include "Define.h"
#include <Arduino.h>

class LCPS {
	public:
		LCPS(int);
		void shutdown();
	private:
		int switchPin;
};

#endif
