// InitialSetup.h

#ifndef _INITIALSETUP_h
#define _INITIALSETUP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Util.h"

class InitialSetupClass
{
 private:
	 int sampleWindow;

 public:
	void settingsMenu();
	void changeSampleWindow();
	void changeAvarageSampleCount();
	void start();
};

extern InitialSetupClass menu;

#endif

