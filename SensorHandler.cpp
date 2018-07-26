// 
// 
// 

#include "SensorHandler.h"
#include "LEDHandler.h"


SensorHandler sensorHandler;

SensorHandler::SensorHandler() : _splSensor(),
								 _hdtSensor(),
								 _splSampleCount(20),
								 _readIndex(0), 
								 _totalDecibels(0.0), 
								 _averageDecibels(0.0)
{
	this->init();
;}

void SensorHandler::init(void)
{
	//_splDecibelReadings.reserve(_splSampleCount);
	for (auto &reading : _splDecibelReadings) {
		reading = 0.0;
	}
}

void SensorHandler::changeSampleCount(int sampleCount) 
{
	if(sampleCount <= 20 && sampleCount >= 1)
		_splSampleCount = sampleCount;
}

int SensorHandler::getSampleCount()
{
	return int(_splSampleCount);
}


void SensorHandler::updateSensors()
{
	_splSensor.update();                        // calculates volts from sensor data
	_hdtSensor.update();
	sensorDataSmoother();
}

void SensorHandler::updateLED()
{
	ledHandler.updateLEDColorLinear(_averageDecibels);   // updates LED color according to decibel data, linear color gradient
}

float SensorHandler::getAverageDecibels(void)
{
	return (float)(_averageDecibels);
}

float SensorHandler::getHumidity()
{
	return _hdtSensor.humidity;
}

float SensorHandler::getTemperature()
{
	return _hdtSensor.temperature;
}

void SensorHandler::sensorDataSmoother()
{
	_totalDecibels = _totalDecibels - _splDecibelReadings[_readIndex];

	_splDecibelReadings[_readIndex] = _splSensor.getDBActual();       // insert newest decibel value

	_totalDecibels = _totalDecibels + _splDecibelReadings[_readIndex];

	_readIndex++;                                                       // advance to the next position in the array:

	if (_readIndex >= _splSampleCount){ 							// if we're at the end of the array...
		_readIndex = 0;                                                   // ...wrap around to the beginning:
	}
	
	_averageDecibels = _totalDecibels / _splSampleCount * 1.0;
}

DecibelData SensorHandler::getDecibelData()
{
	Serial.println("_splSampleCount : " + String(_splSampleCount));
	DecibelData decibels(_splDecibelReadings, _splSampleCount);
	Serial.println("DecibelDataSize: " + String(decibels.getSize()));
	return decibels;
}

void SensorHandler::changeSPLSampleWindow(int window)
{
	_splSensor.changeSampleWindow(window);
}

int SensorHandler::getSPLSampleWindow()
{
	return _splSensor.getSampleWindow();
}

