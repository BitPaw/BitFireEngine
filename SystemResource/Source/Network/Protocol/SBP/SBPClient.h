#pragma once

#include "SBPData.h"

#include <Network/Client.h>
#include <Container/Dictionary.hpp>
#include <Async/Thread.h>

#define ResponseID unsigned int

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
#define ResponseDataStateAnswered  0x02


	struct ResponseData
	{
		unsigned int State;
		unsigned int Time; 
		void* Data;
	};

	typedef void (*PackageBuilderFunction)(SBPData& data, void* payloadBuffer);
	typedef void (*PackageRecieveEvent)(const SBPData& data);


	class SBPClient
	{
		private: 

		Dictionary<ResponseID, ResponseData> _responseLookup;
		static ResponseID _counter;

		ThreadFunctionReturnType SendFileThread(void* data);

		protected:
		Client _client;

		PackageRecieveEvent PackageRecieveCallBack;


		void PackageRecieve(const SBPData& data);
		void PackageDeploy(const SBPData& data);

		// Send
		ResponseID PackageDeploy(const unsigned int source, const unsigned int target, PackageBuilderFunction packageBuilderFunction);


		static void PackageCreateIAM(SBPData& data, void* payloadBuffer);

		static ResponseID ResponseIDGenerate();



		public:
		SBPClient();

		void ConnectToServer(const char* ip, const unsigned short port);
		void ConnectToServer(const wchar_t* ip, const unsigned short port);
		void DisconnectFromServer();

		void RegisterMe();
		void SendText(const char* text);
		void SendFile(const char* filePath);
	};
}