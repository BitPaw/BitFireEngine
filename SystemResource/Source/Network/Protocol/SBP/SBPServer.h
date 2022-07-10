#pragma once

#include "SBPData.h"

#include <Container/Dictionary.hpp>
#include <Network/Server.h>
#include <Network/Protocol/SBP/SBPQueue.h>

namespace BF
{
	class SBPServer :  protected ISocketListener
	{
		protected:
		Server _server;

		SBPQueue _inputQueue;

		Dictionary<ResponseID, Byte__*> _responseLookup;


		virtual void OnSocketCreating(const IPAdressInfo& adressInfo, bool& use);
		virtual void OnSocketCreated(const IPAdressInfo& adressInfo, bool& use);

		virtual void OnMessageSend(IOSocketMessage socketMessage);
		virtual void OnMessageReceive(IOSocketMessage socketMessage);

		// Server Only
		virtual void OnConnectionListening(const IPAdressInfo& adressInfo);
		virtual void OnConnectionLinked(const IPAdressInfo& adressInfo);

		// Client Only
		virtual void OnConnectionEstablished(const IPAdressInfo& adressInfo);
		virtual void OnConnectionTerminated(const IPAdressInfo& adressInfo);


		public:
		void Start(const unsigned short port);
		void Stop();

		void SendFile(const ClientID clientID, const char* text);
		void SendFile(const ClientID clientID, wchar_t* text);

		const ResponseID GenerateResponseID();
		bool SendMessageWaitResponse
		(
			const ClientID clientID,
			const ResponseID responseID,
			const Byte__* buffer, 
			const size_t& bufferSize
		);

		void SendTextToAll(const char* text);
		void SendTextToAll(const wchar_t* text);
		void SendTextToClient(const unsigned int clientID, const char* text);
		void SendTextToClient(const unsigned int clientID, const wchar_t* text);
	};
}