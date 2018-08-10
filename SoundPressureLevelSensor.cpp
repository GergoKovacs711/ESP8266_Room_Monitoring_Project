// 
// 
// 

#include "SoundPressureLevelSensor.h"

double SoundPressureLevelSensor::getDBActual(void)
{
	return _decibel;
}

void SoundPressureLevelSensor::update(void)
{
	updateVolts();
	updateDecibels();
}

void SoundPressureLevelSensor::changeSampleWindow(int window)
{
	if (window > 2 && window <= 20)
		_sampleWindow = window;
}

int SoundPressureLevelSensor::getSampleWindow(void)
{
	return int(_sampleWindow);
}

void SoundPressureLevelSensor::updateVolts(void)
{
	_volt = ((calculatePeakToPeak() * 5.0) / 1024.0) * 0.707;  // convert to RMS voltage
}

void SoundPressureLevelSensor::updateDecibels(void)
{
	// 0 would result in infinite _decibel value
	if (_volt <= 0) _volt = 0.01;	

	// Some of these constants were drawn from the spreedsheet of the sensor..
	// and some were calculated during tuning the sensor
	_decibel = log10(_volt / 0.00631) * 22 + 94 - 44 - 25;
}

	// This method takes the min and max values of the sensor..
	// within a given timeframe and returns their difference.
int SoundPressureLevelSensor::calculatePeakToPeak(void)
{
	int startMillis = millis();  

	int signalMaxValue = 0;           
	int signalMinValue = 1024;        

	int currentReadSignalValue = 0;

	while (millis() - startMillis < _sampleWindow)
	{
		currentReadSignalValue = analogRead(MICROPHONE_PIN);
		if (currentReadSignalValue < 1024)    // filtering out of range values
		{
			if (currentReadSignalValue > signalMaxValue)
			{
				signalMaxValue = currentReadSignalValue;         
			}
			else if (currentReadSignalValue < signalMinValue)
			{
				signalMinValue = currentReadSignalValue;        
			}
		}
	}
	return signalMaxValue - signalMinValue;        
}


