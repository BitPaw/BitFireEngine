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
#include "IPAdressInfo.h"

#define SocketBufferSize 2048u

namespace BF
{
	class IOSocket
	{
		private:
		int GetAdressFamily(IPVersion ipVersion);
		

		public:
		//---<Data>-------------------
		IPAdressInfo AdressInfo;
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
		void Close();
		
		static SocketActionResult Create(IPAdressFamily adressFamily, SocketType socketType, ProtocolMode protocolMode, unsigned int& socketID);

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

		SocketActionResult Receive();
		SocketActionResult Send(const char* message, size_t messageLength);
		SocketActionResult SendFile(const char* filePath, size_t sendBufferSize = 2048);		

#if defined(OSWindows)
		static SocketActionResult WindowsSocketAgentStartup();
		static SocketActionResult WindowsSocketAgentShutdown();
#endif
	};
}