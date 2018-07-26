
#include "WifiHandler.h"

WifiHandler wifiHandler;

void WifiHandler::connect()
{
	WiFi.mode(WIFI_STA);
	ESPWifiMulti.addAP(CustomConstants::wifi_ssid.c_str(), CustomConstants::wifi_pswd.c_str());

	Serial.println();
	Serial.println();
	Serial.print("Wait for WiFi... ");

	while (ESPWifiMulti.run() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(250);
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	delay(500);

}
