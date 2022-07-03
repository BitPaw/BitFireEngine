#pragma once

#include "SBPData.h"

#include <Network/Client.h>
#include <Container/ResponseCache.h>
#include <Async/Thread.h>

namespace BF
{
	enum class ResponseState
	{
		Invalid, // Initialisation value, do not use otherwise

		Waiting, // Package got send, waiting for response

		Finished
	};

	struct ResponseToken
	{
		unsigned char State;
		unsigned char Value;
	};

	struct SendFileThreadData
	{
		char FilePath[PathMaxSize];
		char IP[IPv6LengthMax];
		unsigned short Port;
	};


#define ResponseDataStateInvalid 0x00
#define ResponseDataStateWaiting 0x01
#define ResponseDataStateTimeout  0x02
#define ResponseDataStateAnswered  0x03


	struct ResponseData
	{
		unsigned int State;
		void* Data;
	};

	struct SBPPackageTransfareInfo
	{
		void* InputData;
		size_t InputDataSize;
		void* ResponseData;
		size_t ResponseDataSize;
		ResponseID ID;
	};

	class SBPClient : protected ISocketListener
	{
		private: 
		ResponseCache _responseCache;
		Client _client;

		static ThreadFunctionReturnType ReciveDataThread(void* sbpClient);

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
			const PackageBuilderFunction packageBuilderFunction
		);	

		void ConnectToServer(const char* ip, const unsigned short port);
		void ConnectToServer(const wchar_t* ip, const unsigned short port);
		void DisconnectFromServer();

		void RegisterMe();
		void SendText(const char* text);
		void SendFile(const char* filePath);

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