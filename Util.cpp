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

int Util::readUserInput_Yes_or_No()
{
	int userInput = 0;
	userInput = Serial.read();
	serialFlush();

	if (userInput == 121 || userInput == 89)
	{
		return 1;
	}
	else if (userInput == 78 || 110) {
		return 2;
	}
	else {
		return -1;
	}

}

int Util::waitForUserInput_INT()
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

void Util::init(void)
{
	Serial.begin(CustomConstants::baudRate);
	Serial.println("Serial: OK");
	delay(1000);
}

void Util::serialFlush()
{
	while (Serial.available() > 0)
	{
		char tempChar = Serial.read();
	}
}

int Util::readIntFromSerial()
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

void Util::sendDataToSerialDefault() {
	Serial.println("SPL: " + String(sensorHandler.getAverageDecibels()));
}




