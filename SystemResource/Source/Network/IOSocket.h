#ifndef IOSocketInclude
#define IOSocketInclude

#include "../OSDefine.h"
#include "SocketError.h"
#include "IPVersion.h"

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
		public:
		unsigned int ID;
		unsigned short Port;
		char Message[SocketBufferSize];

		IPVersion IPMode;

		//---[ Events ]------------------------------------------------------------
		void (*OnMessage)(int socketID, char* message);
		void (*OnConnected)(int socketID);
		void (*OnDisconnected)(int socketID);
		//-------------------------------------------------------------------------

		struct sockaddr_in AdressIPv4; // Used only in IPv4

#ifdef OSUnix
		struct addrinfo AdressIPv6;
#elif defined(OSWindows)
		ADDRINFO AdressIPv6;
#endif


		char IsCurrentlyUsed();
		IOSocket();
		SocketError Open(IPVersion ipVersion, unsigned short port);
		void Close();
		void AwaitConnection(IOSocket* clientSocket);
		SocketError Connect(IOSocket* serverSocket, char* ipAdress, unsigned short port);
		SocketError Read();
		SocketError Write(char* message);

		// Private
		int GetAdressFamily(IPVersion ipVersion);
		SocketError SetupAdress(IPVersion ipVersion, char* ip, unsigned short port);

#ifdef OSUnix
		void* ReadAsync();
#elif defined(OSWindows)
		unsigned long ReadAsync();
		SocketError WindowsSocketAgentStartup();
		SocketError WindowsSocketAgentShutdown();
#endif


	};
}
#endif