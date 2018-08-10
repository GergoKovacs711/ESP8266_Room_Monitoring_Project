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
public:
	DecibelData(const double *array, int arraySize);
	
	double at(short place);
	int getSize(void);

 private:
	 const int _size;
	 double _decibels[MAX_DECIBEL_SAMPLE_COUNT];
};
#endif

