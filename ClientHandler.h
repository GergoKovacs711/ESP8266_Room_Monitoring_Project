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
#include "ServerInfo.h"
#include "ESP8266HTTPClient.h"

class ClientHandler
{
public:
	ClientHandler(void);
	void init(void);

	void uploadData(void);

 private:
	 ServerInfo _javaServer;
	 HTTPClient _httpClient;

	 int _retryWindow;

	 String dataStringAppander(void);
	 void sendDataToServer(ServerInfo &server);
	 void httpStatusCodeHandler(int httpStatusHandler, ServerInfo &server);
};

extern ClientHandler clientHandler;

#endif

