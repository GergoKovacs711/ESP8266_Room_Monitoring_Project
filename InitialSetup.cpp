// 
// 
// 

#include "InitialSetup.h"

void InitialSetupClass::settingsMenu(void) 
{
	Serial.println("Which parameter would you like to change? Enter the corresponding number.\n");
	Serial.println("1. Sample window (in ms, 10-1000, default: 25)");
	Serial.println("2. Avarage sample count (3-20, default: 7)");

	if (!Util::waitForInputTimeOut(500, 10000)) 
	{
		Serial.println("Action timed out!");
		return;
	}
	// waits for user input, int only
	int userInput = Util::waitForUserInput_INT();

	switch (userInput)
	{
		// user wants to change the sample window
	case 1:
		Serial.println("You selected 1");
		Serial.println(" ");
		this->changeSampleWindow();
		break;

		// user wants to change the avarage sample count
	case 2:
		Serial.println("You selected 2");
		Serial.println(" ");
		this->changeAvarageSampleCount();
		break;

		// invalid user input
	default:
		Serial.println("Unknown user input! Make sure to only enter one character.");
		Serial.println(" ");
		break;
	}
}

//---------------------------------------------------------------------------//
void InitialSetupClass::changeSampleWindow(void) 
{
	Serial.println("Enter a value for the sample window(10-1000, default: 25).");

	if (!Util::waitForInputTimeOut(500, 10000))
	{
		Serial.println("Action timed out!");
		return;
	}

	// waits for user input, int only
	int userInput = Util::waitForUserInput_INT();      

	// only accepts input between 10-1000
	if (userInput > 9 && userInput < 1001) 
	{    
		sensorHandler.changeSPLSampleWindow(userInput);
		Serial.println("The new sample window value is:");
		Serial.println(sensorHandler.getSPLSampleWindow());
		Serial.println(" ");
		delay(1000);
	}
	// invalid user input
	else 
	{   
		Serial.println("Unknown user input or value out of limits!\n");
	}
}

//---------------------------------------------------------------------------//
void InitialSetupClass::changeAvarageSampleCount(void) 
{
	Serial.println("Enter a value for the sample count(3-20, default: 7).\n");
	
	if (!Util::waitForInputTimeOut(500, 10000)) 
	{
		Serial.println("Action timed out!");
		return;
	}

	// waits for user input, int only
	int userInput = Util::waitForUserInput_INT();                           

	// only accepts input between 3-20
	if (userInput > 2 && userInput <= MAX_DECIBEL_SAMPLE_COUNT) 
	{            
		sensorHandler.changeSampleCount(userInput);
		Serial.println("The new sample window value is:");
		Serial.println(sensorHandler.getSampleCount());
		Serial.println(" ");
		delay(1000);
	}
	// invalid user input
	else 
	{                                                           
		Serial.println("Unknown user input or value out of limits!\n");
	}
}

void InitialSetupClass::start(void) 
{
	Serial.println("Do you wish to use different settings from the default ones? (y/n)");
	boolean keepRunning = true;         // used to run the main while case
	boolean firstRun = true;           // on the second run it goes back straight into settingsMenu()
	int userInput = 0;

	if (!Util::waitForInputTimeOut(500, 5000)) {
		Serial.println("Action timed out!");
		return;
	}

	while (keepRunning) {
		// if not the first run it enters settingsMenu()
		if (!firstRun) {                
			Util::serialFlush();
			this->settingsMenu();
		}
		// On the first run it waits for user input
		else {
			Util::waitForInputTimeOut(500, 10000);                    
			userInput = Util::readUserInput_Yes_or_No();
			Util::serialFlush();

			// user inputs y or Y and intends to change some settings
			if (userInput == 1) {                 
				Serial.println("You selected Y\n");
				Util::serialFlush();
				this->settingsMenu();
			}
			// user inputs n or N the function exits
			else if (userInput == 2) {           
				Serial.println("You selected N\n");
				return;
			}
			// the user entered invalid data
			else {                               
				Serial.println("Unknown user input! Make sure to only enter one character.\n");
			}

			// the function has already run at least once
			firstRun = false;                     
		}

		do {  
			// the function is stuck here until y or Y, or n or N has not been pressed..
			// or until the waitForInputTimeOut times out.

			Serial.println("Do you still wish to change the settings?(y/n)");

			if (!Util::waitForInputTimeOut(500, 10000)) {
				Serial.println("Action timed out!");
				return;
			}

			userInput = Util::readUserInput_Yes_or_No();                      
			Util::serialFlush();

			switch (userInput)
			{
			case 1:
				Serial.println("You selected Y\n");
				break;

			case 2:
				Serial.println("You selected N\n");
				return;

			default:
				Serial.println("Unknown input!\n");
				break;
			}
		} while (userInput != 1);
	}
}

InitialSetupClass menu;

