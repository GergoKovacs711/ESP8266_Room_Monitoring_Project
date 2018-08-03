// 
// 
// 

#include "InitialSetup.h"


void InitialSetupClass::settingsMenu(void) {
	Serial.println("Which parameter would you like to change? Enter the corresponding number.\n");
	Serial.println("1. Sample window (in ms, 10-1000, default: 25)");
	Serial.println("2. Avarage sample count (3-20, default: 7)");

	if (!Util::waitForInputTimeOut(500, 10000)) 
	{
		Serial.println("Action timed out!");
		return;
	}

	int userInput = Util::waitForUserInput_INT();     // waits for user input, int only

	if (userInput == 1) 
	{                    // user wants to change the sample window
		Serial.println("You selected 1");
		Serial.println(" ");
		this->changeSampleWindow();
	}
	else if (userInput == 2) 
	{                // user wants to change the avarage sample count
		Serial.println("You selected 2");
		Serial.println(" ");
		this->changeAvarageSampleCount();
	}
	else 
	{                                    // invalid user input
		Serial.println("Unknown user input! Make sure to only enter one character.");
		Serial.println(" ");
	}
}

//---------------------------------------------------------------------------//
void InitialSetupClass::changeSampleWindow(void) {
	Serial.println("Enter a value for the sample window(10-1000, default: 25).");

	if (!Util::waitForInputTimeOut(500, 10000))
	{
		Serial.println("Action timed out!");
		return;
	}

	int userInput = Util::waitForUserInput_INT();      // waits for user input, int only

	if (userInput > 9 && userInput < 1001) 
	{    // only accepts input between 10-1000
		sensorHandler.changeSPLSampleWindow(userInput);
		Serial.println("The new sample window value is:");
		Serial.println(sensorHandler.getSPLSampleWindow());
		Serial.println(" ");
		delay(1000);
	}
	else 
	{                                      // invalid user input
		Serial.println("Unknown user input or value out of limits!");
		Serial.println(" ");
	}
}

//---------------------------------------------------------------------------//
void InitialSetupClass::changeAvarageSampleCount(void) {
	Serial.println("Enter a value for the sample count(3-20, default: 7).");
	Serial.println(" ");
	
	if (!Util::waitForInputTimeOut(500, 10000)) {
		Serial.println("Action timed out!");
		return;
	}

	int userInput = Util::waitForUserInput_INT();                           // waits for user input, int only

	if (userInput > 2 && userInput <= MAX_DECIBEL_SAMPLE_COUNT)  // only accepts input between 3-20
	{            
		sensorHandler.changeSampleCount(userInput);
		Serial.println("The new sample window value is:");
		Serial.println(sensorHandler.getSampleCount());
		Serial.println(" ");
		delay(1000);
	}
	else {                                                           // invalid user input
		Serial.println("Unknown user input or value out of limits!");
		Serial.println(" ");
	}
}

void InitialSetupClass::start(void) {
	Serial.println("Do you wish to use different settings from the default ones? (y/n)");
	boolean keepRunning = true;         // used to run the main while case
	boolean firstRun = true;           // on the second run it goes back straight into settingsMenu()
	int userInput = 0;

	if (!Util::waitForInputTimeOut(500, 5000)) {
		Serial.println("Action timed out!");
		return;
	}

	while (keepRunning) {
		if (!firstRun) {                // if not the first run it enters settingsMenu()
			Util::serialFlush();
			this->settingsMenu();
		}
		else {
			Util::waitForInput(500);                    // waits for user input
			userInput = Util::readUserInput_Yes_or_No();
			Util::serialFlush();

			if (userInput == 1) {                 // user inputs y or Y and intends to change some settings
				Serial.println("You selected Y");
				Serial.println(" ");
				Util::serialFlush();
				this->settingsMenu();
			}
			else if (userInput == 2) {           // user inputs n or N the function exits
				Serial.println("You selected N");
				Serial.println(" ");
				return;
			}
			else {                                // the user entered invalid data
				Serial.println("Unknown user input! Make sure to only enter one character.");
				Serial.println(" ");
			}

			firstRun = false;                     // the function has run at least once
		}

		do {  // the function is stuck here until y or Y, or n or N has not been pressed
			Serial.println("Do you still wish to change the settings?(y/n)");

			if (!Util::waitForInputTimeOut(500, 10000)) {
				Serial.println("Action timed out!");
				return;
			}

			userInput = Util::readUserInput_Yes_or_No();                      // waits for user input
			Util::serialFlush();

			if (userInput == 1) {                                       // user inputs y or Y and intends to change some more settings
				Serial.println("You selected Y");
				Serial.println(" ");
			}
			else if (userInput == 2) {                                 // user inputs n or N the function exits
				Serial.println("You selected N");
				Serial.println(" ");
				return;
			}
			else {                                                      // the user entered invalid data
				Serial.println("Unknown input!");
				Serial.println(" ");
			}
		} while (userInput != 1);
	}
}

InitialSetupClass menu;

