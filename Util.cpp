// 
// 
// 

#include "Util.h"

using namespace Util;

void Util::waitForInput(int delayTime)
{
	do
	{
		delay(delayTime);
	} while (!Serial.available());
}

int Util::readUserInput_Yes_or_No(void)
{
	int userInput = 0;
	userInput = Serial.read();
	serialFlush();

	// if 121 - y or 89 - Y then returns 1
	if (userInput == 121 || userInput == 89)
	{
		return 1;
	}
	// if 110 - n or 78 - N then returns 2
	else if (userInput == 78 || userInput == 110) {
		return 2;
	}
	// if anything else then returns -1
	else {
		return -1;
	}

}

int Util::waitForUserInput_INT(void)
{
	waitForInput(500);
	int userInput = readIntFromSerial();
	serialFlush();
	return userInput;
}

bool Util::waitForInputTimeOut(int delayTime, int timeOut)
{
	int timeSpent = 0;
	do
	{
		delay(delayTime);
		timeSpent += delayTime;
	} while (!Serial.available() && timeSpent < timeOut);

	return timeSpent < timeOut;
}

void Util::serialInit(void)
{
	Serial.begin(CustomConstants::baudRate);
	Serial.println("Serial: OK");
	delay(1000);
}

void Util::serialFlush(void)
{
	while (Serial.available() > 0)
	{
		char tempChar = Serial.read();
	}
}

int Util::readIntFromSerial(void)
{
	waitForInput(500);
	unsigned int integerValue = 0;
	char incomingByte = 0;

	do
	{
		incomingByte = Serial.read();
		if (incomingByte == -1 || !isAnInteger(incomingByte))
			break;
		integerValue *= 10;
		integerValue = ((incomingByte - 48) + integerValue);
	} while (incomingByte != '\n');

	return integerValue;
}

bool Util::isAnInteger(int inputByte)
{
	return (inputByte > 47 && inputByte < 58);
}

void Util::sendDataToSerial(float averageDecibels) {
	Serial.println("SPL: " + String(averageDecibels));
}

void Util::sendDataToSerialDefault(void) {
	Serial.print("SPL: " + String(sensorHandler.getAverageDecibels()));
	Serial.print("   T: " + String(sensorHandler.getTemperature()));
	Serial.println("   H: " + String(sensorHandler.getHumidity()));
}




