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
	SocketError errorCode = Socket.Connect(&ConnectedServerData, ip, port);

	return errorCode == SocketError::SocketNoError;
}

void BF::Client::SendCommand()
{

}

void BF::Client::Disconnect()
{
	Socket.Close();
}