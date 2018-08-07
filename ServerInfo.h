// ServerInfo.h

#ifndef _SERVERINFO_h
#define _SERVERINFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "CustomConstants.h"

class ServerInfo
{
private:
	
	const String _URLheader;
	const String _contentType;

 public:
	unsigned long lastTimeConnected_InMillis;
	unsigned long lastServerDown_InMillis;
	
	const unsigned int timeToWait;

	const String name;
	const String ip;
	const short port;

	bool unavailable;

	ServerInfo();
	ServerInfo( String serverName,
				String URLHeader,
				String contentType,
				String IP,
				short port,
				unsigned int time);

	static ServerInfo& getJavaServerInfo();
	
	String generateHttpPostMessage(String data);


	
};



#endif

