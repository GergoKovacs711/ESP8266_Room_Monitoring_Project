// 
// 
// 

#include "SensorHandler.h"
#include "LEDHandler.h"


SensorHandler sensorHandler;

SensorHandler::SensorHandler() : _splSensor(),
								 _hdtSensor(),
								 _splSampleCount(MAX_DECIBEL_SAMPLE_COUNT),
								 _readIndex(0), 
								 _totalDecibels(0.0), 
								 _averageDecibels(0.0)
{
	this->init();
}

void SensorHandler::init(void)
{
	for (auto &reading : _splDecibelReadings) {
		reading = 0.0;
	}
}

void SensorHandler::changeSampleCount(int sampleCount) 
{
	if(sampleCount <= MAX_DECIBEL_SAMPLE_COUNT && sampleCount >= 1)
		_splSampleCount = sampleCount;
}

int SensorHandler::getSampleCount(void)
{
	return int(_splSampleCount);
}


void SensorHandler::updateSensors(void)
{
	_splSensor.update();                        
	_hdtSensor.update();
	sensorDataSmoother();
}

void SensorHandler::updateLED(void)
{
	ledHandler.updateLEDColorLinear(_averageDecibels);   // updates LED color according to decibel data, linear color gradient
}

float SensorHandler::getAverageDecibels(void)
{
	return (float)(_averageDecibels);
}

float SensorHandler::getHumidity(void)
{
	return _hdtSensor.humidity;
}

float SensorHandler::getTemperature(void)
{
	return _hdtSensor.temperature;
}

	// Were are using a moving average solution to smooth out spurious data.
	// We add all the recorded decibel values from _splDecibelReadings..
	// to _totalDecibels then divide it by the number of sample count.
	// We go through the _splDecibelReadings array in a round robin manner..
	// replacing the current element form the array with the reading from the...
	// sensor. Then we substract the value from _totalDecibels so that we are..
	// able to calculate an up-to-date _averageDecibels value.
void SensorHandler::sensorDataSmoother(void)
{
	_totalDecibels = _totalDecibels - _splDecibelReadings[_readIndex];

	_splDecibelReadings[_readIndex] = _splSensor.getDBActual();       

	_totalDecibels = _totalDecibels + _splDecibelReadings[_readIndex];

	_readIndex++;                                                       

	if (_readIndex >= _splSampleCount){ 							
		_readIndex = 0;                                                   
	}
	
	_averageDecibels = _totalDecibels / _splSampleCount * 1.0;
}

DecibelData SensorHandler::getDecibelData(void)
{
	DecibelData decibels(_splDecibelReadings, _splSampleCount);
	return decibels;
}

void SensorHandler::changeSPLSampleWindow(int window)
{
	_splSensor.changeSampleWindow(window);
}

int SensorHandler::getSPLSampleWindow(void)
{
	return _splSensor.getSampleWindow();
}

void SensorHandler::hdtTester(void)
{
	while (true)
	{
		_hdtSensor.test();
		delay(250);
	}
}

