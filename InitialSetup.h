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
 public:
	void start(void);
	void settingsMenu(void);

	void changeSampleWindow(void);
	void changeAvarageSampleCount(void);
	
private:
	int _sampleWindow;
};

extern InitialSetupClass menu;

#endif

