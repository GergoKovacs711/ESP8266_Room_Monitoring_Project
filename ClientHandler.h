// ClientHandler.h

#ifndef _CLIENTHANDLER_h
#define _CLIENTHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "WifiHandler.h"
#include "LEDHandler.h"
#include "SensorHandler.h"
#include "DecibelData.h"
#include "CustomConstants.h"
#include "HumidityTemperatureSensor.h"

class ClientHandler
{
 private:
	 unsigned long lastTimeDataWasSentToJavaServer_InMillis;
	 unsigned long timeWhenJAVAServerDownWasDetected_InMillis;
	 unsigned long timeWhenNoServerConnectionWasDetected_InMillis;

	 unsigned long lastTimeDataWasSentToThingSpeak_InMillis;
	 unsigned long timeWhenThingSpeakServerDownWasDetected_InMillis;

	 bool javaServerUnavailable;
	 bool noServerAvailable;
	 bool thingSpeakUnavailable;

 public:
	 ClientHandler();
	 void init();

	 void sendDataToJAVAServer(void);
	 void sendDataToThingSpeak_http();
	 String dataStringAppander();
	 void uploadData();
	 void sendDataToServer();

};

extern ClientHandler clientHandler;

#endif

