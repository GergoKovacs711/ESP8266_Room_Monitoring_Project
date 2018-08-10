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

	 void updateSensors(void);
	 void updateLED(void);

	 float getAverageDecibels(void);
	 float getHumidity(void);
	 float getTemperature(void);

	 DecibelData getDecibelData(void);

	 void changeSampleCount(int sampleCount);
	 int getSampleCount();

	 void changeSPLSampleWindow(int window);
	 int getSPLSampleWindow(void);

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

