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
	if (_volt <= 0) _volt = 0.01;
	_decibel = log10(_volt / 0.00631) * 22 + 94 - 44 - 25;
}

int SoundPressureLevelSensor::calculatePeakToPeak(void)
{
	int startMillis = millis();  // start of sample window

	int signalMax = 0;           // max read singal value
	int signalMin = 1024;        // min read signal value

	int sample = 0;

	// collect data for sampleWindow period of time
	while (millis() - startMillis < _sampleWindow)
	{
		sample = analogRead(MICROPHONE_PIN);
		if (sample < 1024)                // toss out spurious readings
		{
			if (sample > signalMax)
			{
				signalMax = sample;         // save just the max levels
			}
			else if (sample < signalMin)
			{
				signalMin = sample;         // save just the min levels
			}
		}
	}
	return signalMax - signalMin;        // max 
}


