#pragma once

#include <Network/Client.h>
#include <Container/Dictionary.hpp>

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

	class SBPClient
	{
		private:
		//Dictionary<ResponseID, >

		protected:
		Client _client;

		public:
		void ConnectToServer(const char* ip, const unsigned short port);
		void ConnectToServer(const wchar_t* ip, const unsigned short port);
		void DisconnectFromServer();

		void RegisterMe();
		void SendText(const char* text);
		void SendFile(const char* filePath);
	};
}