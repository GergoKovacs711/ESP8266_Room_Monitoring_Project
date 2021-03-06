// HumidityTemperatureSensor.h

#ifndef _HUMIDITYTEMPERATURESENSOR_h
#define _HUMIDITYTEMPERATURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "DHT_sensor_library_for_ESPx/DHTesp.h"
#include "CustomConstants.h"

class HumidityTemperatureSensor
{
public:
	float temperature;
	float humidity;

	HumidityTemperatureSensor(void);

	void update(void);
	void test(void);

private:
	DHTesp _dhtSensor;
};

#endif