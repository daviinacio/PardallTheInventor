#ifndef API_h
#define AIP_h

#include "Define.h"
#include <Arduino.h>

class AIP {
	public:
		AIP();
		AIP(int);					// Port
		AIP(int, int);				// Port, bufferLength
		void setBufferLength(int);
		void run();
		
		int read();
		int get();
		int get(int);
	private:
		int port, bufferLength;
		int * buffer;			// 0 ~ 1024
		
		void clearBuffer();
		void incrementBuffer(int);
};

#endif
