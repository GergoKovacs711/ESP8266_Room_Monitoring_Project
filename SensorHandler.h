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
//#include "CustomConstants.h"

class SensorHandler
{	
 private:
	 
	 SoundPressureLevelSensor _splSensor;

	 short _splSampleCount;
	 //std::vector<double> _splDecibelReadings;
	 double _splDecibelReadings [MAX_DECIBEL_SAMPLE_COUNT];
	 short _readIndex;

	 double _totalDecibels;
	 double _averageDecibels;
	 
	 void sensorDataSmoother(void);

	 void init(void);

 public:
	 SensorHandler(void);

	 void changeSampleCount(int sampleCount);
	 int getSampleCount();

	 void updateSensors(void);
	 void updateLED(void);

	 float getAverageDecibels(void);

	 DecibelData getDecibelData();

	 void changeSPLSampleWindow(int window);
	 int getSPLSampleWindow();
	 
};

extern SensorHandler sensorHandler;


#endif

