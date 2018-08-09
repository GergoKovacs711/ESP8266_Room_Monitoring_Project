// 
// 
// 

#include "ClientHandler.h"

ClientHandler::ClientHandler(void) : _javaServer(),
									 _retryWindow(CustomConstants::clientHandlerRetryWindow),
									 _httpClient()

{

}

void ClientHandler::init(void) 
{
	unsigned long mills = millis();
	long double targetMillis = mills - CustomConstants::clientHandlerTargetMillsWindow;

	if (targetMillis >= 0) {

		_javaServer.lastServerDown_InMillis = targetMillis;
	}
	else
	{
		_javaServer.lastServerDown_InMillis = 0;
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
	int serverDowntime = millis() - _javaServer.lastServerDown_InMillis;
	if (serverDowntime > _javaServer.timeToWait || serverDowntime <= 0)
	{

		this->sendDataToServer(_javaServer);
	}
}

void ClientHandler::sendDataToServer(ServerInfo &server)
{
	if (millis() - server.lastTimeConnected_InMillis > server.timeToWait
		|| millis() - server.lastTimeConnected_InMillis <= 0)
	{
		//_httpClient.begin(String("http://" + CustomConstants::javaHttpURL)
						  //+ String (":" + CustomConstants::javaServerPort) +
						  //"/ServletExample/ESPServlet");

		_httpClient.begin("http://192.168.38.152:8081/ServletExample/ESPServlet");

		ledHandler.setLEDColorTo(ledColor.blue);

		Serial.println("Connected to " + String(server.name));
		_httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");

		_httpClient.setTimeout(CustomConstants::javaHttpTimeOut);

		String data = this->dataStringAppander();

		int httpStatus = _httpClient.POST(data);

		if (httpStatus == HTTP_CODE_OK)
		{
			Serial.print("Data sent to server!");
			Serial.println("Status code: " + String(httpStatus));

			server.lastTimeConnected_InMillis = millis();
			server.unavailable = false;
			delay(200);
		}
		else
		{
			Serial.print("Data couldn't be sent to server!");
			Serial.println("Status code: " + String(httpStatus));
			server.lastServerDown_InMillis = millis();
			server.unavailable = true;
		}

		_httpClient.end();

		ledHandler.setLEDColorTo(ledColor.green);
	}
}
		
ClientHandler clientHandler;

