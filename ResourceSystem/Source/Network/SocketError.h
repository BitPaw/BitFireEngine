#ifndef SocketErrorInclude
#define SocketErrorInclude

namespace BF
{
	enum class SocketError
	{
		SocketNoError,

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

	const char* SocketErrorToString(SocketError socketError);
}

#endif