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

	extern const std::string wifi_ssid;
	extern const std::string wifi_pswd;

	extern const int dhtPin;
	extern const int dhtType;

	extern const String javaServerName;
	extern const String javaServerURL;
	extern const String javaServerContentType;
	extern const String javaServerIP;
	extern const short javaServerPort;
	extern const int javaServerTimeToWait;

	extern const int clientHandlerRetryWindow;
	extern const int clientHandlerTargetMillsWindow;
}

#endif

