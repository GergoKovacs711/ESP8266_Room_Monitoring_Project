// SoundPressureLevelSensor.h

#ifndef _SOUNDPRESSURELEVELSENSOR_h
#define _SOUNDPRESSURELEVELSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SoundPressureLevelSensor
{
 public:
	double getDBActual(void);
	void update(void);

	void changeSampleWindow(int window);
	int getSampleWindow(void);

private:
	const short MICROPHONE_PIN = 0;           // the microphone amplifier output is connected to pin A0

	double _volt = 0;                              // convert to RMS voltage
	double _decibel = 0;                          // the calculated actual decibel value

	short _sampleWindow = 25;

	void updateVolts(void);
	void updateDecibels(void);

	int calculatePeakToPeak(void);
	
};


#endif

