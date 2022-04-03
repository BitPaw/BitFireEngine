#include "SocketType.h"

#include <OS/OSDefine.h>

#if defined(OSUnix)
#include <sys/socket.h>
#elif defined(OSWindows)
#include <WinSock2.h>
#endif

#define SOCK_Invalid 0xFF 

BF::SocketType BF::ConvertSocketType(unsigned int socketType)
{
	switch (socketType)
	{
		case SOCK_STREAM:
			return BF::SocketType::Stream;

		case SOCK_DGRAM:
			return BF::SocketType::Datagram;

		case SOCK_RAW:
			return BF::SocketType::Raw;

		case SOCK_RDM:
			return BF::SocketType::RDM;

		case SOCK_SEQPACKET:
			return BF::SocketType::SeqPacket;

		default:
			return BF::SocketType::Invalid;
	}
}

unsigned int BF::ConvertSocketType(SocketType socketType)
{
	switch (socketType)
	{
		default:
		case BF::SocketType::Invalid:
			return SOCK_Invalid;

		case BF::SocketType::Stream:
			return SOCK_STREAM;

		case BF::SocketType::Datagram:
			return SOCK_DGRAM;

		case BF::SocketType::Raw:
			return SOCK_RAW;

		case BF::SocketType::RDM:
			return SOCK_RDM;

		case BF::SocketType::SeqPacket:
			return SOCK_SEQPACKET;
	}
}