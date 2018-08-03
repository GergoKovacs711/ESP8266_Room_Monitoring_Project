// WifiHandler.h

#ifndef _WIFIHANDLER_h
#define _WIFIHANDLER_h
#include "WifiClient.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "CustomConstants.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class WifiHandler
{
 public:
	 void connect(void);

	 WiFiClient wifiClient;
	 ESP8266WiFiMulti ESPWifiMulti;
};

extern WifiHandler wifiHandler;
#endif

