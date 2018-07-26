// Util.h

#ifndef _UTIL_h
#define _UTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "CustomConstants.h"
#include "SensorHandler.h"

namespace Util
{
	void waitForInput(int delayTime);
	int readUserInput_Yes_or_No();
	int waitForUserInput_INT();

	bool waitForInputTimeOut(int delayTime, int timeOut);
	void init(void);
	void serialFlush();
	int readIntFromSerial();

	bool isAnInteger(int inputByte);
	void sendDataToSerial(float averageDecibels);
	void sendDataToSerialDefault();
}


#endif

