// 
// 
// 

#include "ClientHandler.h"

ClientHandler::ClientHandler(void) : _javaServer(),
									 _retryWindow(CustomConstants::clientHandlerRetryWindow),
									 _httpClient()
{}

void ClientHandler::init(void) 
{
	unsigned long mills = millis();
	long double targetMillis = mills - CustomConstants::clientHandlerTargetMillsWindow;

	if (targetMillis >= 0) 
		_javaServer.lastServerDown_InMillis = targetMillis;
	else
		_javaServer.lastServerDown_InMillis = 0;

	_javaServer.lastTimeConnected_InMillis = millis();
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
		Serial.println("\nConnecting to " + String(server.name) + " server..");
		ledHandler.setLEDColorTo(ledColor.pink);

		_httpClient.begin(server.getFullURL());
		_httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
		_httpClient.setTimeout(server.timeOut);

		String data = this->dataStringAppander();

		Serial.println("Data being sent: " + String(data) + "\n");

		int httpStatus = _httpClient.POST(data);

		httpStatusCodeHandler(httpStatus, server);

		_httpClient.end();

		ledHandler.setLEDColorTo(ledColor.green);
	}
}

void ClientHandler::httpStatusCodeHandler(int httpStatus, ServerInfo &server) {
	switch (httpStatus)
	{
	case HTTP_CODE_OK:
		Serial.print("Data sent to server! ");
		Serial.println("Status code: " + String(httpStatus) + "\n");

		server.lastTimeConnected_InMillis = millis();
		server.unavailable = false;
		delay(200);
		break;

	case HTTPC_ERROR_CONNECTION_REFUSED:
		Serial.print("Server refused the connection or server is unreachable! ");
		Serial.println("Status code: " + String(httpStatus) + "\n");

		server.lastServerDown_InMillis = millis();
		server.unavailable = true;
		break;

	default:
		Serial.print("Unexpected server response!");
		Serial.println("Status code: " + String(httpStatus) + "\n");

		server.lastServerDown_InMillis = millis();
		server.unavailable = true;
		delay(200);
		break;
	}
}
		
ClientHandler clientHandler;

