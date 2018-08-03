// LEDHandler.h

#ifndef _LEDHANDLER_h
#define _LEDHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LEDColor.h"

class LEDHandler
{
 public:
	LEDHandler(void);

	void init(void );
	void start(void);

	void setLEDColorTo(const RgbColor &rgb_ledColor);
	void updateLEDColorLinear(double currentDB);

private:
	const uint16_t PIXEL_COUNT = 1;
	const uint16_t PIXEL_PIN = 5;
	const uint16_t LED_ADDRESS = 0;

	const int _minLEDdb = 20;
	const int _maxLEDdb = 80;

	// initialised with pixelLED(PIXEL_COUNT, PIXEL_PIN) in .cpp
	NeoPixelBus<NeoRgbFeature, NeoEsp8266BitBang800KbpsMethod>
		_pixelLED;

	short _currentLEDlevel = 0;
};

extern LEDHandler ledHandler;

#endif

