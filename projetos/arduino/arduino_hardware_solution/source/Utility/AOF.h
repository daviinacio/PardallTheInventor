#ifndef AOF_h
#define AOF_h

#include "Define.h"
#include <Arduino.h>

class AOF {
	public:
		// Constructor
		AOF();
		AOF(int);							// Initialize with the port				// NUMBER
		AOF(int, int);						// Initialize with the port and dT		// NUMBER
		
		// Setter
		void set(int);						// Set the value						// BYTE(0 - 255)
		void setPWM(int);					// Set the value without fade			// BYTE(0 - 255)
		void setBreaking(int);				// Set the value with out thread		// BYTE(0 - 255)
		void setBreaking(int, int);			// Set breaking with a temp interval	// BYTE(0 - 255)
		void setInterval(int);				// Set the interval						// MS
		
		// Getter
		int get();							// Get the current output value			// BYTE(0 - 255)
		int getVf();						// Get the final value					// BYTE(0 - 255)
		bool isFinished();
		
		void run(); 						// Update the output value				// NULL
	private:
		int port, output;
		long  dT, To, T, Vo, V;
		
		bool isOutOfBorders(int);
};

#endif
