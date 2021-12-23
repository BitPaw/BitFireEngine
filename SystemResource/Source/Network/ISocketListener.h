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

		virtual void OnMessageSend(IOSocketMessage socketMessage) = 0;
		virtual void OnMessageReceive(IOSocketMessage socketMessage) = 0;	

		// Server Only
		virtual void OnConnectionListening(const IPAdressInfo& adressInfo) = 0;
		virtual void OnConnectionLinked(const IPAdressInfo& adressInfo) = 0;

		// Client Only
		virtual void OnConnectionEstablished(const IPAdressInfo& adressInfo) = 0;
		virtual void OnConnectionTerminated(const IPAdressInfo& adressInfo) = 0;


	};
}