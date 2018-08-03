// LEDColor.h

#ifndef _LEDCOLOR_h
#define _LEDCOLOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <NeoPixelBus.h>

struct LEDColor
{
 public:
	LEDColor(void);

	const RgbColor red;
	const RgbColor green;
	const RgbColor blue;
	const RgbColor pink;
	const RgbColor black;
	const RgbColor defaultLEDColor;
};

extern LEDColor ledColor;

#endif

