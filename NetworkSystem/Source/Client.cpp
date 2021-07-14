#include "Client.h"
#include "Server.h"

#include <stdio.h>
#include <string.h>

BF::Client::Client()
{
	IP = 0;
	ConnectedServerID = -1;
}

char BF::Client::ConnectToServer(char* ip, unsigned short port)
{
	SocketError errorCode = Connect(&ConnectedServerData, ip, port);

	return errorCode == SocketNoError;
}

void BF::Client::SendCommand()
{

}

void BF::Client::Disconnect()
{
	Close();	
}