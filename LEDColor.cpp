// 
// 
// 

#include "LEDColor.h"

LEDColor ledColor;			// The adafruit sensor uses GRB instead of RGB..
							// therefore red and green values has been swapped..
							// within their constructor.
						
LEDColor::LEDColor(void) :  red				(0,  50,  0),
							green			(50,  0,  0),
							blue			( 0,  0, 25),
							pink			( 0, 15,  3),
							black			( 0,  0,  0),
							defaultLEDColor	( 20, 20, 20)


{}

