#pragma once

#include "IOSocketMessage.h"
#include "IPAdressInfo.h"

namespace BF
{
	struct ISocketListener
	{
		public:				
		virtual void OnSocketCreating(const IPAdressInfo& adressInfo, bool& use) = 0;
		virtual void OnSocketCreated(const IPAdressInfo& adressInfo, bool& use) = 0;

		virtual void OnConnectionLinked(int socketID) = 0;
		virtual void OnConnectionListening(int socketID) = 0;
		virtual void OnConnectionEstablished(int socketID) = 0;
		virtual void OnConnectionTerminated(int socketID) = 0;

		virtual void OnMessageSend(IOSocketMessage socketMessage) = 0;
		virtual void OnMessageReceive(IOSocketMessage socketMessage) = 0;
	};
}