// 
// 
// 

#include "ClientHandler.h"

ClientHandler::ClientHandler(void) : lastTimeDataWasSentToJavaServer_InMillis(0),
								 timeWhenJavaServerDownWasDetected_InMillis(0),
								 timeWhenNoServerConnectionWasDetected_InMillis(0),
								 lastTimeDataWasSentToThingSpeak_InMillis(0),
								 timeWhenThingSpeakServerDownWasDetected_InMillis(0),
							 	 javaServerUnavailable(false),
								 noServerAvailable(false),
								 thingSpeakUnavailable(false)

{}

void ClientHandler::init(void)
{
	noServerAvailable = true;
	unsigned long mills = millis();
	long double targetMillis = mills - 50000;

	if (targetMillis >= 0) {
		timeWhenNoServerConnectionWasDetected_InMillis = targetMillis;
	}
	else
	{
		timeWhenNoServerConnectionWasDetected_InMillis = 0;
	}
	
}

void ClientHandler::sendDataToJAVAServer(void) 
{
	if (millis() - lastTimeDataWasSentToJavaServer_InMillis > 1000
		|| millis() - lastTimeDataWasSentToJavaServer_InMillis <= 0) 
	{
		if (wifiHandler.wifiClient.connect(CustomConstants::javaServerIP, CustomConstants::javaServerPort))
		{
			ledHandler.setLEDColorTo(ledColor.pink);

			String data = this->dataStringAppander();

			Serial.println("Connected to server. Sending data.");
			Serial.println("Data being sent:" + data);

			wifiHandler.wifiClient.print("POST /ServletExample/ESPServlet HTTP/1.1\n");
			wifiHandler.wifiClient.print("Host: " + CustomConstants::javaServerIP + "\n");
			wifiHandler.wifiClient.print("Content-Type: application/x-www-form-urlencoded\n");
			wifiHandler.wifiClient.print("Content-Length: ");
			wifiHandler.wifiClient.print(data.length());
			wifiHandler.wifiClient.print("\n\n");
			wifiHandler.wifiClient.println(data);

			delay(200);

			Serial.println("Data sent to server!");

			if (!wifiHandler.wifiClient.connected()) 
			{
				wifiHandler.wifiClient.stop();
			}

			wifiHandler.wifiClient.flush();
			wifiHandler.wifiClient.stop();

			lastTimeDataWasSentToJavaServer_InMillis = millis();
			javaServerUnavailable = false;
			ledHandler.setLEDColorTo(ledColor.green);
		}
		else 
		{
			Serial.println("Could not connect to server!");

			timeWhenJavaServerDownWasDetected_InMillis = millis();
			javaServerUnavailable = true;
		}
	}
}

String ClientHandler::dataStringAppander(void)
{	
	DecibelData decibels = sensorHandler.getDecibelData();
	int decibelValue_int = int(decibels.at(0));
	String data = "d=" + String(decibelValue_int);

	for (short counter = 1; counter < decibels.getSize(); counter++)
	{
		decibelValue_int = int(decibels.at(counter));
		data += "&d=" + String(decibelValue_int);
	}
	data += "&t=" + String(int(sensorHandler.getTemperature()));
	data += "&h=" + String(int(sensorHandler.getHumidity()));

	return data;
}

void ClientHandler::uploadData(void)
{	
	if (noServerAvailable) 
	{
		int serversDowntime = millis() - timeWhenNoServerConnectionWasDetected_InMillis;
		if (serversDowntime > 60000 || serversDowntime <= 0) 
		{
			this->sendDataToServer();
		}
	}
	else 
	{
		this->sendDataToServer();
	}
}

void ClientHandler::sendDataToServer(void)
{
	if (!javaServerUnavailable) 
	{
		sendDataToJAVAServer();
	}
	else 
	{
		int serverDowntime = millis() - timeWhenJavaServerDownWasDetected_InMillis;
		if (serverDowntime > 30000 || serverDowntime <= 0) 
		{
			sendDataToJAVAServer();
		}
		else 
		{
			if (!thingSpeakUnavailable) 
			{
				sendDataToThingSpeak_http();
			}
			else 
			{
				int serverDowntime = millis() - timeWhenThingSpeakServerDownWasDetected_InMillis;
				if (serverDowntime > 30000 || serverDowntime <= 0) 
				{
					sendDataToThingSpeak_http();
				}
				else 
				{
					noServerAvailable = true;
				}
			}
		}
	}
}

void ClientHandler::sendDataToThingSpeak_http(void)
{
	if (millis() - lastTimeDataWasSentToThingSpeak_InMillis > 20000
		|| millis() - lastTimeDataWasSentToThingSpeak_InMillis <= 0)
	{
		if (wifiHandler.wifiClient.connect(CustomConstants::thingSpeakApiURL, CustomConstants::thingSpeakPort))
		{
			ledHandler.setLEDColorTo(ledColor.pink);

			String data = "field2=" + String(int(sensorHandler.getAverageDecibels()));

			Serial.println("Connected to ThingSpeak. Sending data.");
			Serial.println("Data being sent: " + data);

			wifiHandler.wifiClient.print("POST /update HTTP/1.1\n");
			wifiHandler.wifiClient.print("Host: api.thingspeak.com\n");
			wifiHandler.wifiClient.print("Connection: close\n");
			wifiHandler.wifiClient.print("X-THINGSPEAKAPIKEY: " + String(CustomConstants::thingSpeakWriteAPIKey.c_str()) + "\n");
			wifiHandler.wifiClient.print("Content-Type: application/x-www-form-urlencoded\n");
			wifiHandler.wifiClient.print("Content-Length: ");
			wifiHandler.wifiClient.print(data.length());
			wifiHandler.wifiClient.print("\n\n");
			wifiHandler.wifiClient.println(data);

			delay(200);

			Serial.println("Data sent to ThingSpeak!");

			if (!wifiHandler.wifiClient.connected())
			{
				wifiHandler.wifiClient.stop();
			}

			wifiHandler.wifiClient.flush();
			wifiHandler.wifiClient.stop();

			lastTimeDataWasSentToThingSpeak_InMillis = millis();
			thingSpeakUnavailable = false;

			ledHandler.setLEDColorTo(ledColor.green);
		}
		else
		{
			Serial.println("Could not connect to ThingSpeak!");

			timeWhenThingSpeakServerDownWasDetected_InMillis = millis();
			thingSpeakUnavailable = true;
		}
	}
}

ClientHandler clientHandler;

