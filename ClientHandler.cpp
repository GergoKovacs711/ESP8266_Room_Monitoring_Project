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
									 thingSpeakUnavailable(false),
									 javaServer()

{
	
}

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

void ClientHandler::javaInit() 
{
	unsigned long mills = millis();
	long double targetMillis = mills - 50000;

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

void ClientHandler::uploadDataJavaServerOnly(int timeToWait = 10000)
{
	int serverDowntime = millis() - javaServer.lastServerDown_InMillis;
	if (serverDowntime > timeToWait || serverDowntime <= 0)
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


void ClientHandler::delegateToServer(void)
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

void ClientHandler::uploadData(void)
{
	if (noServerAvailable)
	{
		int serversDowntime = millis() - timeWhenNoServerConnectionWasDetected_InMillis;
		if (serversDowntime > 60000 || serversDowntime <= 0)
		{
			this->delegateToServer();
		}
	}
	else
	{
		this->delegateToServer();
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

			String tempData = "POST /ServletExample/ESPServlet HTTP/1.1\n";
			tempData += "Host: " + String(CustomConstants::javaServerIP) + "\n";
			tempData += "Content-Type: application/x-www-form-urlencoded\n";
			tempData += "Content-Length: " + String(data.length()) + "\n\n" + data;

			if (wifiHandler.wifiClient.connected())
			{
				wifiHandler.wifiClient.println(tempData.c_str());
				Serial.println("Data sent to server!");
				delay(200);
			}
			else
			{
				Serial.println("Server connection lost before data sending!");
			}
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

ClientHandler clientHandler;

