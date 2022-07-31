#pragma once

//#include <Network/Client.h>
//#include <Async/Thread.h>
#include <Container/ResponseCache.h>

//#include "SBPData.h"
#include "SBPResult.h"
#include "SBPDataPackage.h"

#include <Network/Client.h>

namespace BF
{
	class SBPClient : protected ISocketListener
	{
		private: 
		ResponseCache _responseCache;
		Client _client;

		static ThreadResult ReciveDataThread(void* sbpClient);

		public:
		wchar_t Name[256];

		SBPClient* SubConnectionList;
		size_t SubConnectionListSize;

		SBPClient();

		// Sending a message via a socket, await a response.
		SBPResult SendAndWaitResponse
		(
			void* inputData,
			const size_t inputDataSize,
			void* responseData,
			size_t& responseDataSize,

			const unsigned int sourceID,
			const unsigned int targetID,
			const SBPDataPackage* dataPackage
		);	



		void ConnectToServer(const char* ip, const unsigned short port);
		void ConnectToServer(const wchar_t* ip, const unsigned short port);
		void DisconnectFromServer();

		void RegisterMe();
		void SendText(const char* text);
		void SendFile(const char* filePath);

		// Geerbt �ber ISocketListener
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