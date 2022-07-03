#pragma once

namespace BF
{
	enum class SocketActionResult
	{
		InvalidResult,
		Successful,


		OuputBufferTooSmal,


		SocketInavlidAdressFamily,
		SocketCreationFailure,
		SocketOptionFailure,
		SocketBindingFailure,
		SocketListeningFailure,

		SocketSendFailure,
		SocketRecieveFailure,
		SocketRecieveConnectionClosed,

		SocketFlagsInvalid,
		NameServerReturnedTemporaryFailureIndication,
		NameServerReturnedPermanentFailureIndication,
		SocketTypeNotSupported,
		RequestedAddressFamilyNotSupported,
		OutOfMemory,
		HostExistsButHasNoData,
		HostHasNoNetworkAddresses,

		IPOrPortNotKnown,

		SocketIsNotConnected,

		RequestedServiceNotAvailableForSocket,

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

		WindowsSocketSystemNotInitialized,
		//----------------------------------------

		// File IO
		FileNotFound
	};

	const char* SocketActionResultToString(SocketActionResult SocketActionResult);
}