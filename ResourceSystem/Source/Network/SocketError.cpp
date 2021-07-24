#include "SocketError.h"

const char* SocketErrorToString(SocketError socketError)
{
	switch (socketError)
	{
		case SocketNoError:
			return "no error";

		case	SocketInavlidAdressFamily:
			return "socket inavlid adressfamily";

		case	SocketCreationFailure:
			return "Socket creation failure";

		case	SocketOptionFailure:
			return "Socket option failure";

		case	SocketBindingFailure:
			return "Socket binding failure";

		case	SocketListeningFailure:
			return "socket listening failure";

		case	SocketSendFailure:
			return "socket send failure";

		case	SocketRecieveFailure:
			return "socket recieve failure";

		case SocketRecieveConnectionClosed:
			return "Socket Recieve Connection Closed";

		case	SocketConnectionFailure:
			return "Socket Connection Failure";

		case	SubSystemNotReady:
			return "Windows: Sub System NotR eady";

		case	VersionNotSupported:
			return "Windows: VersionNotSupported";

		case	BlockedByOtherOperation:
			return "Windows: BlockedByOtherOperation";

		case	LimitReached:
			return "Windows: LimitReached";

		case	InvalidParameter:
			return "Windows: InvalidParameter";

		case	SubSystemNotInitialised:
			return "Windows: SubSystemNotInitialised";

		case	SubSystemNetworkFailed:
			return "Windows: SubSystemNetworkFailed";

		case	SocketIsBlocking:
			return "Windows: SocketIsBlocking";
		default:
			return "Illegeal command";
	}
}