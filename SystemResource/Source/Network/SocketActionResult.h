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


		// Server
		NoClientWithThisID,
		NoSendEmptyData,


		//---[ Windows Only (WindowsSocketAgent) ]-------
		SubSystemNotReady,
		VersionNotSupported,
		BlockedByOtherOperation,
		LimitReached,
		InvalidParameter,
		SubSystemNotInitialised,
		SubSystemNetworkFailed,
		SocketIsBlocking,
		//----------------------------------------

		// File IO
		FileNotFound
	};

	const char* SocketActionResultToString(SocketActionResult SocketActionResult);
}