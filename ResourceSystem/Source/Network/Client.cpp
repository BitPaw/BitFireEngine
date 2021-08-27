#include "Client.h"
#include "Server.h"

#include <stdio.h>
#include <string.h>

BF::Client::Client()
{
	IP = 0;
	ConnectedServerID = -1;
}

BF::SocketError BF::Client::ConnectToServer(char* ip, unsigned short port)
{
	return Socket.Connect(&ConnectedServerData, ip, port);
}

void BF::Client::SendCommand()
{

}

void BF::Client::Disconnect()
{
	Socket.Close();
}