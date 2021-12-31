#include "ServerListeningThreadInfo.h"

BF::ServerListeningThreadInfo::ServerListeningThreadInfo()
{
	ServerSocket = nullptr;
	ServerAdress = nullptr;
}

BF::ServerListeningThreadInfo::ServerListeningThreadInfo(IOSocket* serverSocket, Server* server)
{
	ServerSocket = serverSocket;
	ServerAdress = server;
}