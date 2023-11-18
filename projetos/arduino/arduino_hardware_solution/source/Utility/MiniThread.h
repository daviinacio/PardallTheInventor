#ifndef MINITHREAD_h
#define MINITHREAD_h

#include "Define.h"
#include <Arduino.h>

class MiniThread {
	public:
		// Constructor
		MiniThread();						// Initialize without interval			// NULL
		MiniThread(int);					// Initialize with interval				// MS
		
		// Setter
		void setInterval(int);				// Set the interval						// MS
		
		// Function
		bool isFinished();					// Check if is finished					// NULL
		void reset();						// Reset the thread						// NULL
		
	private:
		long To, dT;
};

#endif
