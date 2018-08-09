// 
// 
// 

#include "ServerInfo.h"

ServerInfo::ServerInfo( String serverName,
						String URLHeader,
						String contentType,
						String IP,
						short prt,
						unsigned int timeToWait,
						unsigned int timeOut)
										     :	 name			(serverName),
												 _URLheader		(URLHeader),
												 _contentType	(contentType),
												 ip				(IP),
												 port			(prt),
												 timeToWait		(timeToWait),
												 timeOut		(timeOut),
												 unavailable	(false)
{}

ServerInfo::ServerInfo() :  name			(CustomConstants::javaServerName),
							_URLheader		(CustomConstants::javaServerURL),
							_contentType	(CustomConstants::javaServerContentType),
							ip				(CustomConstants::javaServerIP),
							port			(CustomConstants::javaServerPort),
							timeToWait		(CustomConstants::javaServerTimeToWait),
							timeOut			(CustomConstants::javaServerTimeOut),
							unavailable		(false)
{}

ServerInfo& ServerInfo::getJavaServerInfo()
{	
	ServerInfo serverInfo ( CustomConstants::javaServerName,
							CustomConstants::javaServerURL,
							CustomConstants::javaServerContentType,
							CustomConstants::javaServerIP,
							CustomConstants::javaServerPort,
							CustomConstants::javaServerTimeToWait,
							CustomConstants::javaServerTimeOut);
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

String ServerInfo::getFullURL() {
	return String ( "http://" 
					+ CustomConstants::javaServerIP 
					+ ":" 
					+ CustomConstants::javaServerPort 
					+ CustomConstants::javaURLTrail);
}






