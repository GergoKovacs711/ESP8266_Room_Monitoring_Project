// DecibelData.h

#ifndef _DECIBELDATA_h
#define _DECIBELDATA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "CustomConstants.h"

class DecibelData
{
 private:
	 double _decibels[MAX_DECIBEL_SAMPLE_COUNT];
	 const int _size;
 public:
	 
	 DecibelData(const double *array, int arraySize);
	 double at(short place);
	 int getSize();

};
#endif

