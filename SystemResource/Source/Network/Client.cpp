#include "Client.h"

#include <stdio.h>

BF::Client::Client()
{
	strncpy(IP, "127.0.0.1", 10);
	ConnectedServerID = -1;
}

BF::SocketActionResult BF::Client::ConnectToServer(const char* ip, unsigned short port)
{
	strncpy(IP, ip, IPSize);

	SocketActionResult socketActionResult = Connect(ConnectedServerData, IP, port);

    CommunicationThread = new std::thread([](Client* client)
    {
        while (client->IsCurrentlyUsed())
        {
            SocketActionResult socketActionResult = client->Receive();           
        }

    }, this);

    return socketActionResult;
}

void BF::Client::Disconnect()
{
	Close();
}