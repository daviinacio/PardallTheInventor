#ifndef BUFFER_h
#define BUFFER_h

class Buffer {
	public:
		//Buffer();
		Buffer(int);						// BufferLength
		Buffer(int, int);					// BufferLength
		void setLength(int);
		
		char get(int);
		
		void clear();
		void clear(char);
		void increment(char);
	private:
		int bufferLength;
		char * buffer;
		int null_var;
};

#endif
