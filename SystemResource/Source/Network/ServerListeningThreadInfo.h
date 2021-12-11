#pragma once

#include "Server.h"

namespace BF
{
	struct ServerListeningThreadInfo
	{
		public:
		IOSocket* ServerSocket;
		Server* ServerAdress;	

		ServerListeningThreadInfo();
		ServerListeningThreadInfo(IOSocket* serverSocket, Server* server);
	};
}