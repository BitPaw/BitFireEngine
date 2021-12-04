#pragma once

#include "IOSocketMessage.h"

namespace BF
{
	struct ISocketListener
	{
		public:				
		virtual void OnConnectionLinked(int socketID) = 0;
		virtual void OnConnectionListening(int socketID) = 0;
		virtual void OnConnectionEstablished(int socketID) = 0;
		virtual void OnConnectionTerminated(int socketID) = 0;

		virtual void OnMessageSend(IOSocketMessage socketMessage) = 0;
		virtual void OnMessageReceive(IOSocketMessage socketMessage) = 0;
	};
}