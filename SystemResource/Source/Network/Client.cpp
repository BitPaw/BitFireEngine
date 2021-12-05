#include "Client.h"

#include <stdio.h>

BF::Client::Client()
{
	strncpy_s(IP, "127.0.0.1", 10);
	ConnectedServerID = -1;
}

BF::SocketActionResult BF::Client::ConnectToServer(const char* ip, unsigned short port)
{
	strncpy_s(IP, ip, IPSize); 

	SocketActionResult socketActionResult = Connect(ConnectedServerData, IP, port);

    CommunicationThread.Create(Client::CommunicationFunctionAsync, this);

    return socketActionResult;
}

void BF::Client::Disconnect()
{
	Close();
}

ThreadFunctionReturnType BF::Client::CommunicationFunctionAsync(void* data)
{
    IOSocket* ioSocket = (IOSocket*)data;

    while (ioSocket->IsCurrentlyUsed())
    {
        SocketActionResult socketActionResult = ioSocket->Receive();

        if (socketActionResult != SocketActionResult::Successful)
        {
            ioSocket->Close();
        }
    }  

    return 0;
}