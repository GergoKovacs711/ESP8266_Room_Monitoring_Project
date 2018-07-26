// HumidityTemperatureSensor.h

#ifndef _HUMIDITYTEMPERATURESENSOR_h
#define _HUMIDITYTEMPERATURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <DHT.h>
#include "CustomConstants.h"

class HumidityTemperatureSensor
{
	const int _dhtSensorPin;
	DHT _dhtSensor;

public:
	float temperature;
	float humidity;

	HumidityTemperatureSensor();

	void update(void);
};

#endif