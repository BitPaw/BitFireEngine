#pragma once

#include "../../Network/Server.h"

#define PortHTTP 80

namespace BF
{
	class HTTPServer : public Server, public IServerListener,public ISocketListener
	{
		public:
		void MessageParse(const char* message);

		// Geerbt über IServerListener
		virtual void OnClientConnected(Client& client) override;
		virtual void OnClientDisconnected(Client& client) override;
		virtual void OnClientAcceptFailure() override;

		// Geerbt über ISocketListener
		virtual void OnSocketCreating(const IPAdressInfo& adressInfo, bool& use) override;
		virtual void OnSocketCreated(const IPAdressInfo& adressInfo, bool& use) override;
		virtual void OnMessageSend(IOSocketMessage socketMessage) override;
		virtual void OnMessageReceive(IOSocketMessage socketMessage) override;
		virtual void OnConnectionListening(const IPAdressInfo& adressInfo) override;
		virtual void OnConnectionLinked(const IPAdressInfo& adressInfo) override;
		virtual void OnConnectionEstablished(const IPAdressInfo& adressInfo) override;
		virtual void OnConnectionTerminated(const IPAdressInfo& adressInfo) override;
	};
}