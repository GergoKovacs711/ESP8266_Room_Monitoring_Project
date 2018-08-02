// CustomConstants.h

#ifndef _CUSTOMCONSTANTS_h
#define __CUSTOMCONSTANTS_h_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <string>


namespace CustomConstants
{
#define MAX_DECIBEL_SAMPLE_COUNT 20

	extern const unsigned long baudRate;
	//const int MAX_DECIBEL_SAMPLE_COUNT;

	extern const std::string wifi_ssid;
	extern const std::string wifi_pswd;

	extern const unsigned long thingSpeakChannelNumber;
	extern const std::string thingSpeakWriteAPIKey;

	extern const String thingSpeakApiURL;
	extern const short thingSpeakPort;

	extern const String javaServerIP;
	extern const short javaServerPort;

	extern const int dhtPin;
	extern const int dhtType;
}

#endif

