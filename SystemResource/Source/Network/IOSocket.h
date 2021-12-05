#pragma once

#include "../OSDefine.h"

#ifdef OSUnix
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define AdressInfoType struct addrinfo
#elif defined(OSWindows)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#define AdressInfoType ADDRINFOA
#endif

#include "SocketActionResult.h"
#include "IPVersion.h"
#include "ISocketListener.h"
#include "IPAdressFamily.h"
#include "ProtocolMode.h"
#include "SocketType.h"
#include "../Async/Thread.h"

#define SocketBufferSize 2048u

namespace BF
{
	class IOSocket
	{
		private:
		int GetAdressFamily(IPVersion ipVersion);
		
		SocketActionResult SetupAdress
		(
			char* ip, // null for any ipAdress
			unsigned short port, // -1 for no port
			IPAdressFamily ipMode,			
			SocketType socketType,
			ProtocolMode protocolMode
		);

#if defined(OSWindows)
		SocketActionResult WindowsSocketAgentStartup();
		SocketActionResult WindowsSocketAgentShutdown();
#endif

		public:
		//---<Data>-------------------
		unsigned int ID;
		unsigned short Port;
		AdressInfoType AdressInfo;		
		//----------------------------

		//---<Internal IO>------------
		char BufferMessage[SocketBufferSize];
		Thread CommunicationThread;
		//----------------------------

		//---<Event CallBack>---------
		ISocketListener* EventCallBackSocket;
		//----------------------------


		IOSocket();

		char IsCurrentlyUsed();

		bool GetIP(char* buffer, size_t bufferSize);

		bool GetIPAndPort(char* ip, unsigned short& port);

		void Close();
		void AwaitConnection(IOSocket& clientSocket);
		
		SocketActionResult Open
		(
			unsigned short port, 
			IPAdressFamily ipAdressFamily = IPAdressFamily::Unspecified,
			SocketType socketType = SocketType::Stream,
			ProtocolMode protocolMode = ProtocolMode::Any
		);		
		
		SocketActionResult Connect(IOSocket& serverSocket, const char* ipAdress, unsigned short port);
		SocketActionResult Receive();
		SocketActionResult Send(const char* message, size_t messageLength);
		SocketActionResult SendFile(const char* filePath, size_t sendBufferSize = 2048);		
	};
}