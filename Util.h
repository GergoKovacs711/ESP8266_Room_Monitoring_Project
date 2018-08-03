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
	void serialInit(void);
	void serialFlush(void);

	void waitForInput(int delayTime);
	bool waitForInputTimeOut(int delayTime, int timeOut);
	int waitForUserInput_INT(void);

	int readIntFromSerial(void);
	int readUserInput_Yes_or_No(void);

	void sendDataToSerial(float averageDecibels);
	void sendDataToSerialDefault(void);

	bool isAnInteger(int inputByte);
}
#endif

