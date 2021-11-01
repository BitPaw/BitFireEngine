#include "Client.h"

#include <stdio.h>

BF::Client::Client()
{
	strncpy(IP, "127.0.0.1", 10);
	ConnectedServerID = -1;
}

BF::SocketActionResult BF::Client::ConnectToServer(const char* ip, unsigned short port)
{
	strncpy(IP, ip, 10);

	return Connect(ConnectedServerData, IP, port);
}

void BF::Client::Disconnect()
{
	Close();
}