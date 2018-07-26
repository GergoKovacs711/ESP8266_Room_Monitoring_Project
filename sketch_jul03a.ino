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

void setup() 
{
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
	sensorHandler.updateSensors();
	sensorHandler.updateLED();
	Util::sendDataToSerialDefault();                      // writes volt and decibel date to serial port
	clientHandler.uploadData();

	delay(50);
}





