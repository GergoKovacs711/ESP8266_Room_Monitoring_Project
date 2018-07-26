
#include "CustomConstants.h"

namespace CustomConstants
{
	const unsigned long baudRate = 115200;
	//int MAX_DECIBEL_SAMPLE_COUNT = 20;

	const std::string wifi_ssid("Shadow");
	const std::string wifi_pswd("H4rcs4b4jusz!");

	const unsigned long thingSpeakChannelNumber = 536845;
	const std::string thingSpeakWriteAPIKey("3P73KNNYTOZ0SWEP");

	const String thingSpeakApiURL = "api.thingspeak.com";
	const short thingSpeakPort = 80;

	const String javaServerIP = "192.168.38.152";
	const short javaServerPort = 8081;

	const uint8_t dhtPin = 4;
	const uint8_t dhtType = 22;     //dht22 = 22; dht11 = 11; dht21 = 21; AM2301 = 21
}