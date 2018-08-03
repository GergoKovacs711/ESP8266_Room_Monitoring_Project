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
public:
	ClientHandler(void);
	void init(void);

	void sendDataToServer(void);
	void sendDataToJAVAServer(void);
	void sendDataToThingSpeak_http(void);

	void uploadData(void);

	String dataStringAppander(void);

 private:
	 unsigned long lastTimeDataWasSentToJavaServer_InMillis;
	 unsigned long timeWhenJavaServerDownWasDetected_InMillis;
	 unsigned long timeWhenNoServerConnectionWasDetected_InMillis;

	 unsigned long lastTimeDataWasSentToThingSpeak_InMillis;
	 unsigned long timeWhenThingSpeakServerDownWasDetected_InMillis;

	 bool javaServerUnavailable;
	 bool noServerAvailable;
	 bool thingSpeakUnavailable;
};

extern ClientHandler clientHandler;

#endif

