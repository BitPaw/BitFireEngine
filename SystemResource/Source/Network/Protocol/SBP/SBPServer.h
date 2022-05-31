#pragma once

#include <Network/Server.h>
#include <File/ByteCluster.h>

#define SBPIDText MakeInt('T', 'e', 'x', 't')
#define SBPIDFile MakeInt('F', 'i', 'l', 'e')

namespace BF
{
	class SBPServer
	{
		protected:
		Server _server;

		void CreateText(const char* text, Byte* buffer, size_t& bufferSize, const size_t bufferSizeMax);
		void CreateText(const wchar_t* text, Byte* buffer, size_t& bufferSize, const size_t bufferSizeMax);

		public:
		void Start(const unsigned short port);
		void Stop();

		void SendFile(const char* text);
		void SendFile(const wchar_t* text);

		void SendTextToAll(const char* text);
		void SendTextToAll(const wchar_t* text);
		void SendTextToClient(const unsigned int clientID, const char* text);
		void SendTextToClient(const unsigned int clientID, const wchar_t* text);
	};
}