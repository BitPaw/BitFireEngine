#ifndef SocketErrorInclude
#define SocketErrorInclude

typedef enum SocketError_
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


}SocketError;

const char* SocketErrorToString(SocketError socketError);

#endif