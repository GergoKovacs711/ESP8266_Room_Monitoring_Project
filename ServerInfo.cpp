// 
// 
// 

#include "ServerInfo.h"

ServerInfo::ServerInfo( String serverName,
						String URLHeader,
						String contentType,
						String IP,
						short prt,
						unsigned int time)

										     :	 name			(serverName),
												 _URLheader		(URLHeader),
												 _contentType	(contentType),
												 ip				(IP),
												 port			(prt),
												 timeToWait		(time),
												 unavailable	(false)
{}

ServerInfo::ServerInfo() :  name			("Java"),
							_URLheader		("/ServletExample/ESPServlet HTTP/1.1"),
							_contentType	("application/x-www-form-urlencoded"),
							ip				(CustomConstants::javaServerIP),
							port			(CustomConstants::javaServerPort),
							timeToWait		(10000),
							unavailable		(false)
{}

ServerInfo& ServerInfo::getJavaServerInfo()
{	
	ServerInfo serverInfo(  "Java",
							"/ServletExample/ESPServlet HTTP/1.1",
							"application/x-www-form-urlencoded",
							CustomConstants::javaServerIP,
							CustomConstants::javaServerPort,
							3000);
								
	return serverInfo;
}

String ServerInfo::generateHttpPostMessage(String data)
{
	Serial.println("Data being sent:" + data);

	String tempData = "POST " + _URLheader + "\n";
	tempData += "Host: " + String(ip) + "\n";
	tempData += "Content-Type: " + _contentType + "\n";
	tempData += "Content-Length: " + String(data.length()) + "\n\n" + data;

	return tempData;
}






