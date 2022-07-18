#pragma once

#include <OS/OSVersion.h>

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

#define SocketDebug 1

namespace BF
{
	enum class SocketState
	{
		NotInitialised,

		// Client only

		Connecting,
		Connected,

		DataReceiving,
		DataSending,

		FileReceiving,
		FileSending,

		// Server only
		WaitingForConnection, // listenung



		IDLE
	};

	typedef void (*SocketCreatingEvent)(const IPAdressInfo& adressInfo, bool& use);
	typedef void (*SocketCreatedEvent)(const IPAdressInfo& adressInfo, bool& use);

	typedef void (*MessageSendEvent)(IOSocketMessage socketMessage);
	typedef void (*MessageReceiveEvent)(IOSocketMessage socketMessage);

	// Server Only
	typedef void (*ConnectionListeningEvent)(const IPAdressInfo& adressInfo);
	typedef void (*ConnectionLinkedEvent)(const IPAdressInfo& adressInfo);

	// Client Only
	typedef void (*ConnectionEstablishedEvent)(const IPAdressInfo& adressInfo);
	typedef void (*ConnectionTerminatedEvent)(const IPAdressInfo& adressInfo);

	class IOSocket
	{
		public:
		SocketState State;

		//---<Data>-------------------
		IPAdressInfo AdressInfo;
		//----------------------------

		//---<Internal IO>------------
		ThreadID CommunicationThread;
		//----------------------------

		//---<Event CallBack>---------
		ISocketListener* EventCallBackSocket;
		//----------------------------


		IOSocket();
		~IOSocket();

		bool IsCurrentlyUsed();
		void Close();

		void StateChange(const SocketState socketState);

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

		SocketActionResult Send(const void* inputBuffer, const size_t inputBufferSize);
		SocketActionResult Receive(void* outputBuffer, const size_t outputBufferSizeMax, size_t& outputBufferSizeWritten);

#if defined(OSWindows)
		static SocketActionResult WindowsSocketAgentStartup();
		static SocketActionResult WindowsSocketAgentShutdown();
#endif
	};
}
