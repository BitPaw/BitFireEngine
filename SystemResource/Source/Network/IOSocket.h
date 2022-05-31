#pragma once

#include <OS/OSDefine.h>

#define SocketBufferSize 2048u

#ifdef OSUnix
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define AdressInfoType struct addrinfo
#define AdressInfoDelete freeaddrinfo
#elif defined(OSWindows)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#define AdressInfoType ADDRINFOA
#define AdressInfoDelete FreeAddrInfoA
#endif

#include "SocketActionResult.h"
#include "IPVersion.h"
#include "IPAdressFamily.h"
#include "ProtocolMode.h"
#include "SocketType.h"
#include "IPAdressInfo.h"
#include "ISocketListener.h"

#include <Async/Thread.h>
#include <File/File.h>

#define ClientID unsigned int

namespace BF
{
	class IOSocket
	{	
		public:
		//---<Data>-------------------
		IPAdressInfo AdressInfo;
		//----------------------------

		//---<Internal IO>------------
		Thread CommunicationThread;
		//----------------------------

		//---<Event CallBack>---------
		ISocketListener* EventCallBackSocket;
		//----------------------------


		IOSocket();

		bool IsCurrentlyUsed();
		void Close();
		
		static SocketActionResult Create
		(
			const IPAdressFamily adressFamily, 
			const SocketType socketType,
			const ProtocolMode protocolMode,
			size_t& socketID
		);

		static SocketActionResult SetupAdress
		(
			char* ip, // null for any ipAdress
			unsigned short port, // -1 for no port
			IPAdressFamily ipMode,
			SocketType socketType,
			ProtocolMode protocolMode,
			size_t& adressInfoListSize,
			IPAdressInfo** adressInfoList
		);

		SocketActionResult Receive(Byte* message, const size_t messageLength);
		SocketActionResult Send(const Byte* message, const size_t messageLength);
		SocketActionResult SendFile(const char* filePath, const size_t sendBufferSize = 2048);

#if defined(OSWindows)
		static SocketActionResult WindowsSocketAgentStartup();
		static SocketActionResult WindowsSocketAgentShutdown();
#endif
	};
}