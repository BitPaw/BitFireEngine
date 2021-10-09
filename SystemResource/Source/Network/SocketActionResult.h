#pragma once

namespace BF
{
	enum class SocketActionResult
	{
		InvalidResult,
		Successful,

		SocketInavlidAdressFamily,
		SocketCreationFailure,
		SocketOptionFailure,
		SocketBindingFailure,
		SocketListeningFailure,

		SocketSendFailure,
		SocketRecieveFailure,
		SocketRecieveConnectionClosed,

		// Client
		SocketConnectionFailure,


		//---[ Windows Only (WindowsSocketAgent) ]-------
		SubSystemNotReady,
		VersionNotSupported,
		BlockedByOtherOperation,
		LimitReached,
		InvalidParameter,
		SubSystemNotInitialised,
		SubSystemNetworkFailed,
		SocketIsBlocking
		//----------------------------------------
	};

	const char* SocketActionResultToString(SocketActionResult SocketActionResult);
}