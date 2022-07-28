#ifndef ActionResultInclude
#define ActionResultInclude

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum ActionResult_
	{
		ResultInvalid,

		// File


		ResultSuccessful,

		ResultEmptyPath,

		// Classic
		ResultFileNotFound,
		ResultOutOfMemory,
		ResultFileEmpty,

		ResultWriteFailure,

		//
		ResultFileOpenFailure,
		ResultFileCloseFailure,
		ResultFileReadFailure,
		ResultFileCopyFailure,
		ResultFileCreateFailure,

		ResultFileMemoryMappingFailed,

		// Parsing
		ResultInvalidHeaderSignature,
		ResultInvalidVersion,

		ResultFormatNotSupported,
		ResultFormatNotAsExpected,








		// Socket
		SocketOuputBufferTooSmal,
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
	}
	ActionResult;

#ifdef __cplusplus
}
#endif

#endif