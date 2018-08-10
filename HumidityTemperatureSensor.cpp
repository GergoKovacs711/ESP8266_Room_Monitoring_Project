#include "HumidityTemperatureSensor.h"

HumidityTemperatureSensor::HumidityTemperatureSensor(void) :_dhtSensor()

{
	_dhtSensor.setup(CustomConstants::dhtPin, DHTesp::DHT11);
}

void HumidityTemperatureSensor::update(void)
{
	float readTemperature = _dhtSensor.getTemperature();
	float readHumidity = _dhtSensor.getHumidity();

	temperature = readTemperature;
	humidity = readHumidity;

	if (isnan(readTemperature))
	{
		temperature = 0.0;
	}
	if (isnan(readHumidity))
	{
		humidity = 0.0;
	}
}

void HumidityTemperatureSensor::test(void)
{
	this->update();
	Serial.println("\nStatus: " + String(_dhtSensor.getStatusString()));
	Serial.println("Humidity: " + String(humidity));
	Serial.println("Temperature: " + String(temperature));
}
