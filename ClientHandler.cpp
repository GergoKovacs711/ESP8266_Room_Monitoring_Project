// 
// 
// 

#include "ClientHandler.h"

ClientHandler::ClientHandler(void) : javaServer(),
									 retryWindow(CustomConstants::clientHandlerRetryWindow)

{}

void ClientHandler::init(void) 
{
	unsigned long mills = millis();
	long double targetMillis = mills - CustomConstants::clientHandlerTargetMillsWindow;

	if (targetMillis >= 0) {

		javaServer.lastServerDown_InMillis = targetMillis;
	}
	else
	{
		javaServer.lastServerDown_InMillis = 0;
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

void ClientHandler::uploadData()
{
	int serverDowntime = millis() - javaServer.lastServerDown_InMillis;
	if (serverDowntime > javaServer.timeToWait || serverDowntime <= 0)
	{
		this->sendDataToServer(javaServer);
	}
}

void ClientHandler::sendDataToServer(ServerInfo &server)
{
	if (millis() - server.lastTimeConnected_InMillis > server.timeToWait
		|| millis() - server.lastTimeConnected_InMillis <= 0)
	{
		if (wifiHandler.wifiClient.connect(server.ip, server.port))
		{
			ledHandler.setLEDColorTo(ledColor.blue);

			Serial.println("Connected to " + String(server.name));

			String data = this->dataStringAppander();

			String httpMessage = server.generateHttpPostMessage(data);
			
			if (wifiHandler.wifiClient.connected())
			{
				wifiHandler.wifiClient.println(httpMessage.c_str());
				Serial.println("Data sent to server!");

				server.lastTimeConnected_InMillis = millis();
				server.unavailable = false;
				delay(200);
			}
			else
			{
				Serial.println("Server connection lost before data sending!");
				server.lastServerDown_InMillis = millis();
				server.unavailable = true;
			}

			if (!wifiHandler.wifiClient.connected())
			{
				wifiHandler.wifiClient.stop();
			}
			else
			{	
				wifiHandler.wifiClient.flush();
				wifiHandler.wifiClient.stop();
			}

			
			ledHandler.setLEDColorTo(ledColor.green);
		}
		else
		{
			Serial.println("Could not connect to server!");

			server.lastServerDown_InMillis = millis();
			server.unavailable = true;
		}
	}
}

ClientHandler clientHandler;

