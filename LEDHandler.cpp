// 
// 
// 

#include "LEDHandler.h"

LEDHandler::LEDHandler(void) : _pixelLED(PIXEL_COUNT, PIXEL_PIN)
{
}

void LEDHandler::init(void)
{
	_pixelLED.Begin();
	setLEDColorTo(ledColor.blue);
}

void LEDHandler::start(void)
{
	setLEDColorTo(ledColor.black);
}

void LEDHandler::setLEDColorTo(const RgbColor &rgb_ledColor = ledColor.defaultLEDColor)
{
	_pixelLED.SetPixelColor(LED_ADDRESS, rgb_ledColor);
	_pixelLED.Show();
	delay(10);
}

void LEDHandler::updateLEDColorLinear(double currentDB) {
	if (currentDB <= _minLEDdb) {                          // if decibel is too low than the LED is green
		_pixelLED.SetPixelColor(LED_ADDRESS, ledColor.green);
	}
	else if (currentDB >= _maxLEDdb) {                     // if decibel is too high than the LED is green
		_pixelLED.SetPixelColor(LED_ADDRESS, ledColor.red);
	}
	else {                                                // between minLEDdb and maxLEDdb the color changes in a linear fashion
		double progress = (currentDB - _minLEDdb) / (_maxLEDdb - _minLEDdb);
		_pixelLED.SetPixelColor(LED_ADDRESS, RgbColor::LinearBlend(ledColor.green, ledColor.red, progress));
	}
	_pixelLED.Show();
}


LEDHandler ledHandler;

