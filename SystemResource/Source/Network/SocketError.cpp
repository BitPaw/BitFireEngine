#include "SocketError.h"

const char* BF::SocketErrorToString(SocketError socketError)
{
	switch (socketError)
	{
		case SocketError::SocketNoError:
			return "no error";

		case	SocketError::SocketInavlidAdressFamily:
			return "socket inavlid adressfamily";

		case	SocketError::SocketCreationFailure:
			return "Socket creation failure";

		case	SocketError::SocketOptionFailure:
			return "Socket option failure";

		case	SocketError::SocketBindingFailure:
			return "Socket binding failure";

		case	SocketError::SocketListeningFailure:
			return "socket listening failure";

		case	SocketError::SocketSendFailure:
			return "socket send failure";

		case	SocketError::SocketRecieveFailure:
			return "socket recieve failure";

		case SocketError::SocketRecieveConnectionClosed:
			return "Socket Recieve Connection Closed";

		case	SocketError::SocketConnectionFailure:
			return "Socket Connection Failure";

		case	SocketError::SubSystemNotReady:
			return "Windows: Sub System NotR eady";

		case	SocketError::VersionNotSupported:
			return "Windows: VersionNotSupported";

		case	SocketError::BlockedByOtherOperation:
			return "Windows: BlockedByOtherOperation";

		case	SocketError::LimitReached:
			return "Windows: LimitReached";

		case	SocketError::InvalidParameter:
			return "Windows: InvalidParameter";

		case	SocketError::SubSystemNotInitialised:
			return "Windows: SubSystemNotInitialised";

		case	SocketError::SubSystemNetworkFailed:
			return "Windows: SubSystemNetworkFailed";

		case	SocketError::SocketIsBlocking:
			return "Windows: SocketIsBlocking";
		default:
			return "Illegeal command";
	}
}