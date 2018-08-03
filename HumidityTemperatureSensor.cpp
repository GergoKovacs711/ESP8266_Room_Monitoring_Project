#include "HumidityTemperatureSensor.h"

HumidityTemperatureSensor::HumidityTemperatureSensor(void) :_dhtSensor()

{
	_dhtSensor.setup(CustomConstants::dhtPin, DHTesp::DHT11);
}

void HumidityTemperatureSensor::update(void)
{
	float tempTemperature = _dhtSensor.getTemperature();
	float tempHumidity = _dhtSensor.getHumidity();

	temperature = tempTemperature;
	humidity = tempHumidity;

	if (isnan(tempTemperature))
	{
		temperature = 0.0;
	}
	if (isnan(tempHumidity))
	{
		humidity = 0.0;
	}
}

void HumidityTemperatureSensor::test(void)
{
	this->update();
	Serial.println("Humidity: " + String(humidity));
	Serial.println("Temperature: " + String(temperature));

}
