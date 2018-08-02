//////////////////////////////////////////////////////
////////////////////  Includes  //////////////////////
//////////////////////////////////////////////////////

//#include "CustomConstants.h"
#include "InitialSetup.h"
#include "DecibelData.h"
#include "ClientHandler.h"
#include "SensorHandler.h"
#include "LEDHandler.h"
#include "ThingSpeak.h"
#include "Util.h"
//#include "SerialCommunication.h"
//#include "WifiHandler.h"
#include "DHT_sensor_library_for_ESPx/DHTesp.h"

DHTesp dht;

void setup() 
{
  dht.setup(4, DHTesp::DHT11);
  ledHandler.init();                         // initializing LED HW, sets LED color to blue
  Util::init();								 // starting serial channel
  
  menu.start();							// the user may change some settings here
  wifiHandler.connect();
  clientHandler.init();
  //sensorHandler.init(sampleCount);
  ledHandler.start();                        // sets LED color to black
}

void loop()
{
	//hdtTest();
	//sensorHandler.hdtTester();
	sensorHandler.updateSensors();
	sensorHandler.updateLED();
	Util::sendDataToSerialDefault();                      // writes volt and decibel date to serial port
	clientHandler.uploadData();

	delay(50);
}




