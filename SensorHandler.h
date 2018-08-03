// SensorHandler.h

#ifndef _SENSORHANDLER_h
#define _SENSORHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SoundPressureLevelSensor.h"
#include "DecibelData.h"
#include "HumidityTemperatureSensor.h"

class SensorHandler
{	
 public:
	 SensorHandler(void);

	 void changeSampleCount(int sampleCount);
	 int getSampleCount();

	 void updateSensors(void);
	 void updateLED(void);

	 float getAverageDecibels(void);
	 float getHumidity();
	 float getTemperature();

	 DecibelData getDecibelData();

	 void changeSPLSampleWindow(int window);
	 int getSPLSampleWindow();

	 void hdtTester(void);
	
private:

	SoundPressureLevelSensor _splSensor;
	HumidityTemperatureSensor _hdtSensor;

	short _splSampleCount;
	double _splDecibelReadings[MAX_DECIBEL_SAMPLE_COUNT];
	short _readIndex;

	double _totalDecibels;
	double _averageDecibels;

	void init(void);

	void sensorDataSmoother(void);
};

extern SensorHandler sensorHandler;


#endif

