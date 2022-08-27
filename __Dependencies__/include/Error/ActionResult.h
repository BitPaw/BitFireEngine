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
		ResultFormatInvalid,
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




		// POSIX Error codes, these are pre-defined
		UnkownError, // OTHER

		PermissionDenied, // ACCES
		AddressInUse, // ADDRINUSE
		AddressNotAvailable, // ADDRNOTAVAIL
		AddressFamilyNotSupported, // AFNOSUPPORT
		ResourceUnavailableTryAgain, // AGAIN
		ConnectionAlreadyInProgress, // ALREADY
		ArgumentListTooLong, // 2BIG
		BadFileDescriptor, // BADF
		BadMessage, // BADMSG
		DeviceOrResourceBusy, // BUSY
		OperationCanceled,// CANCELED
		NoChildProcesses, // CHILD
		ConnectionAborted, // CONNABORTED
		ConnectionRefused, // CONNREFUSED
		ConnectionReset, // CONNRESET
		ResourceDeadlockWouldOccur, // DEADLK
		DestinationAddressRequired, // DESTADDRREQ
		MathematicsArgumentOutOfDomainOfFunction, // DOM
		FileExists, // EXIST
		BadAddress, // FAULT
		FileTooLarge, // FBIG
		HostIsUnreachable, // HOSTUNREACH
		IdentifierRemoved, // IDRM
		IllegalByteSequence, // ILSEQ
		OperationInProgress, // INPROGRESS
		InterruptedFunction, // INTR
		InvalidArgument, // INVAL
		IOFailure, // IO
		SocketIsConnected, // ISCONN
		IsADirectory, // ISDIR
		TooManyLevelsOfSymbolicLinks, // LOOP
		FileDescriptorValueTooLarge, // MFILE
		TooManyLinks, // MLINK
		MessageTooLarge, // MSGSIZE
		FilenameTooLong, // NAMETOOLONG
		NetworkIsDown, // NETDOWN
		ConnectionAbortedByNetwork, // NETRESET
		NetworkUnreachable, // NETUNREACH
		TooManyFilesOpenInSystem, // NFILE
		NoBufferSpaceAvailable, // NOBUFS
		NoMessageIsAvailableOnTheStreamHeadReadQueue, // NODATA
		NoSuchDevice, // NODEV
		NoSuchFileOrDirectory, // NOENT
		ExecutableFileFormatError, // NOEXEC
		NoLocksAvailable, // NOLCK
		LinkHasBeenSevered, // NOLINK
		OutOfMemory, // NOMEM
		NoMessageOfTheDesiredType, // NOMSG
		ProtocolNotAvailable, // NOPROTOOPT
		NoSpaceLeftOnDevice, // NOSPC
		NoStreamResources, // NOSR
		NotAStream, // NOSTR
		FunctionNotSupported, // NOSYS
		TheSocketIsNotConnected, // NOTCONN
		NotADirectory, // NOTDIR
		DirectoryNotEmpty, // NOTEMPTY
		StateNotRecoverable, // NOTRECOVERABLE
		NotASocket, // NOTSOCK
		NotSupported, // NOTSUP
		InappropriateIOControlOperation, // NOTTY
		NoSuchDeviceOrAddress, // NXIO
		OperationNotSupportedOnSocket, // OPNOTSUPP
		ValueTooLargeToBeStoredInDataType, // OVERFLOW
		PreviousOwnerDied, // OWNERDEAD
		OperationNotPermitted, // PERM
		BrokenPipe, // PIPE
		ProtocolError, // PROTO
		ProtocolNotSupported, // PROTONOSUPPORT
		ProtocolWrongTypeForSocket, // PROTOTYPE
		ResultTooLarge, // RANGE,
		ReadOnlyFileSystem, //ROFS
		InvalidSeek, // SPIPE
		NoSuchProcess, // SRCH
		StreamTimeout, // TIME -> ioctl()
		ConnectionTimedOut, // TIMEDOUT
		TextFileBusy, // TXTBSY
		OperationWouldBlock, // WOULDBLOCK
		CrossDeviceLink // XDEV









	}
	ActionResult;

	extern ActionResult ConvertErrorCode(const int errorCode);
	extern ActionResult GetCurrentError();

#ifdef __cplusplus
}
#endif

#endif