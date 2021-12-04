#pragma once

#include "Client.h"

namespace BF
{
	class IServerListener
	{
		public:
		virtual void OnClientConnected(Client& client) = 0;
		virtual void OnClientDisconnected(Client& client) = 0;
	};
}