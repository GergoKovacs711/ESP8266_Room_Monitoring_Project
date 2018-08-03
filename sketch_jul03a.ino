
#include "InitialSetup.h"
#include "DecibelData.h"
#include "ClientHandler.h"
#include "SensorHandler.h"
#include "LEDHandler.h"
#include "ThingSpeak.h"
#include "Util.h"
#include "DHT_sensor_library_for_ESPx/DHTesp.h"

DHTesp dht;
uint8_t pin = 4;

void setup() 
{
  dht.setup(pin, DHTesp::DHT11);
  ledHandler.init();                         // initializing LED HW, sets LED color to blue
  Util::serialInit();								 // starting serial channel
  
  menu.start();							// the user may change some settings here
  wifiHandler.connect();
  clientHandler.init();
  //sensorHandler.init(sampleCount);
  ledHandler.start();                        // sets LED color to black
}

void loop()
{
	//sensorHandler.hdtTester();
	sensorHandler.updateSensors();
	sensorHandler.updateLED();
	Util::sendDataToSerialDefault();                      // writes volt and decibel date to serial port
	clientHandler.uploadData();

	delay(50);
}




