#include "HumidityTemperatureSensor.h"

HumidityTemperatureSensor::HumidityTemperatureSensor() :_dhtSensorPin(10),
														_dhtSensor(CustomConstants::dhtPin,
														CustomConstants::dhtType)

{
}

void HumidityTemperatureSensor::update(void)
{
	float tempTemperature = _dhtSensor.readTemperature();
	float tempHumidity = _dhtSensor.readHumidity();

	if (isnan(temperature) || isnan(tempHumidity)) {
		temperature = 0.0;
		humidity = 0.0;
	}
	else
	{
		temperature = tempTemperature;
		humidity = tempHumidity;
	}
}