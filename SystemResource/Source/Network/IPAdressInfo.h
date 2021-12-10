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

#include "ProtocolMode.h"
#include "IPAdressFamily.h"
#include "SocketType.h"

#define IPv6LengthMax 65

namespace BF
{
	struct IPAdressInfo
	{
		public:
		// Runtime Stuff
		unsigned int SocketID;



		char IP[IPv6LengthMax];
		unsigned short Port;

		ProtocolMode Protocol; // 0 or IPPROTO_xxx for IPv4and IPv6
		IPAdressFamily Family; // PF_xxx
		SocketType Type;   // SOCK_xxx


		char IPRawByte[IPv6LengthMax];
		size_t IPRawByteSize;

		int                 ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
		//size_t              ai_addrlen;     // Length of ai_addr
		//char* ai_canonname;   // Canonical name for nodename
		//_Field_size_bytes_(ai_addrlen) struct sockaddr* ai_addr;        // Binary address
		//struct addrinfo* ai_next;        // Next structure in linked list

		IPAdressInfo();
		IPAdressInfo(ADDRINFOA& adressInfo);

		void ConvertFrom(ADDRINFOA& adressInfo);
		void ConvertTo(ADDRINFOA& adressInfo);
	};
}