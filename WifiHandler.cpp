
#include "WifiHandler.h"

WifiHandler wifiHandler;

void WifiHandler::connect(void)
{
	WiFi.mode(WIFI_STA);
	ESPWifiMulti.addAP(CustomConstants::wifi_ssid.c_str(), 
						CustomConstants::wifi_pswd.c_str());

	Serial.print("\n\nWaiting for the WiFi... ");

	while (ESPWifiMulti.run() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(250);
	}

	Serial.println("\nWiFi connected \nIP address: ");
	Serial.println(WiFi.localIP().toString() + "\n");
	delay(500);

}
