#include "SocketActionResult.h"

const char* BF::SocketActionResultToString(SocketActionResult SocketActionResult)
{
	switch (SocketActionResult)
	{
		case SocketActionResult::Successful:
			return "no error";

		case	SocketActionResult::SocketInavlidAdressFamily:
			return "socket inavlid adressfamily";

		case	SocketActionResult::SocketCreationFailure:
			return "Socket creation failure";

		case	SocketActionResult::SocketOptionFailure:
			return "Socket option failure";

		case	SocketActionResult::SocketBindingFailure:
			return "Socket binding failure";

		case	SocketActionResult::SocketListeningFailure:
			return "socket listening failure";

		case	SocketActionResult::SocketSendFailure:
			return "socket send failure";

		case	SocketActionResult::SocketRecieveFailure:
			return "socket recieve failure";

		case SocketActionResult::SocketRecieveConnectionClosed:
			return "Socket Recieve Connection Closed";

		case	SocketActionResult::SocketConnectionFailure:
			return "Socket Connection Failure";

		case	SocketActionResult::SubSystemNotReady:
			return "Windows: Sub System NotR eady";

		case	SocketActionResult::VersionNotSupported:
			return "Windows: VersionNotSupported";

		case	SocketActionResult::BlockedByOtherOperation:
			return "Windows: BlockedByOtherOperation";

		case	SocketActionResult::LimitReached:
			return "Windows: LimitReached";

		case	SocketActionResult::InvalidParameter:
			return "Windows: InvalidParameter";

		case	SocketActionResult::SubSystemNotInitialised:
			return "Windows: SubSystemNotInitialised";

		case	SocketActionResult::SubSystemNetworkFailed:
			return "Windows: SubSystemNetworkFailed";

		case	SocketActionResult::SocketIsBlocking:
			return "Windows: SocketIsBlocking";
		default:
			return "Illegeal command";
	}
}