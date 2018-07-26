// LEDColor.h

#ifndef _LEDCOLOR_h
#define _LEDCOLOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LEDColor
{

 public:
	 LEDColor();
	 const RgbColor red =		RgbColor( 0, 50,  0);         
	 const RgbColor green =		RgbColor(50,  0,  0);         
	 const RgbColor blue =		RgbColor( 0,  0, 50);
	 const RgbColor black =		RgbColor( 0,  0,  0);
	 const RgbColor pink =		RgbColor( 0, 10,  2);
};



#endif

