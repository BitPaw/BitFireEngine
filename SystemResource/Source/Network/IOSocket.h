#pragma once

#include "SocketActionResult.h"
#include "IPVersion.h"
#include "ISocketListener.h"
#include "../OSDefine.h"

#include <thread>

#ifdef OSUnix
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#elif defined(OSWindows)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#endif

#define SocketBufferSize 2048u

namespace BF
{
	class IOSocket
	{
		private:
		int GetAdressFamily(IPVersion ipVersion);
		SocketActionResult SetupAdress(IPVersion ipVersion, const char* ip, unsigned short port);

#if defined(OSWindows)
		SocketActionResult WindowsSocketAgentStartup();
		SocketActionResult WindowsSocketAgentShutdown();
#endif

		public:
		unsigned int ID;
		unsigned short Port;
		char BufferMessage[SocketBufferSize];
		IPVersion IPMode;

		ISocketListener* EventCallBackSocket;
		std::thread* CommunicationThread;	

		struct sockaddr_in AdressIPv4; // Used only in IPv4

#if defined(OSUnix)
		struct addrinfo AdressIPv6;
#elif defined(OSWindows)
		ADDRINFO AdressIPv6;
#endif		

		IOSocket();

		char IsCurrentlyUsed();

		static bool ResolveDomainName(const char* domainName, char* ip);

		void Close();
		void AwaitConnection(IOSocket& clientSocket);
		SocketActionResult Open(IPVersion ipVersion, unsigned short port);	
		SocketActionResult Connect(IOSocket& serverSocket, const char* ipAdress, unsigned short port);
		SocketActionResult Receive();
		SocketActionResult Send(const char* message, size_t messageLength);
		SocketActionResult SendFile(const char* filePath, size_t sendBufferSize = 2048);
	};
}