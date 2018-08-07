// ServerType.h

#ifndef _SERVERTYPE_h
#define _SERVERTYPE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum ServerType
{
	Java
};

#endif

