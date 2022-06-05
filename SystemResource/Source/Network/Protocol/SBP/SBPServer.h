#pragma once

#include "SBPData.h"

#include <Network/Server.h>
#include <Container/Dictionary.hpp>
#include <File/ByteCluster.h>
#include <Network/Protocol/SBP/SBPQueue.h>

namespace BF
{
	struct SBPFile
	{
		unsigned short PathSourceSize;

		union 
		{
			char* TextA;
			wchar_t* TextW;
		} PathSource;

		unsigned short PathTargetSize;

		union
		{
			char* TextA;
			wchar_t* TextW;
		} PathTarget;

		size_t FileSize; // HAs to be 8 Byte!

		// S:N T:N => Invalid
		// S:N T:Y => Create
		// S:Y T:N => Delete
		// S:Y T:Y => Copy

	};

#define ResponseID unsigned int

	class SBPServer : protected ISocketListener
	{
		protected:
		Server _server;

		SBPQueue _inputQueue;

		Dictionary<ResponseID, Byte*> _responseLookup;



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




		void CreateText(const char* text, Byte* buffer, size_t& bufferSize, const size_t bufferSizeMax);
		void CreateText(const wchar_t* text, Byte* buffer, size_t& bufferSize, const size_t bufferSizeMax);

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
			const Byte* buffer, 
			const size_t& bufferSize
		);

		void SendTextToAll(const char* text);
		void SendTextToAll(const wchar_t* text);
		void SendTextToClient(const unsigned int clientID, const char* text);
		void SendTextToClient(const unsigned int clientID, const wchar_t* text);
	};
}