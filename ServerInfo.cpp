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

ServerInfo::ServerInfo() :  name			(CustomConstants::javaServerName),
							_URLheader		(CustomConstants::javaServerURL),
							_contentType	(CustomConstants::javaServerContentType),
							ip				(CustomConstants::javaServerIP),
							port			(CustomConstants::javaServerPort),
							timeToWait		(CustomConstants::javaServerTimeToWait),
							unavailable		(false)
{}

ServerInfo& ServerInfo::getJavaServerInfo()
{	
	ServerInfo serverInfo ( CustomConstants::javaServerName,
							CustomConstants::javaServerURL,
							CustomConstants::javaServerContentType,
							CustomConstants::javaServerIP,
							CustomConstants::javaServerPort,
							CustomConstants::javaServerTimeToWait);
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






