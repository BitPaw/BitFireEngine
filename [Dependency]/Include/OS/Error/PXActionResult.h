#ifndef PXActionResultInclude
#define PXActionResultInclude

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum PXActionResult_
	{
		//---<General>-----------------------
		PXActionInvalid, // Default iniitlialisation value, no not use.
		PXActionSuccessful, // PXAction finished successful
		PXActionFailedAllocation, // A call to malloc failed due to not enough memory or the buffer is too big to fit in a free memory block. [NOMEM]
		PXActionDeniedNoPermission,
		//-----------------------------------
		
		PXActionRefuedInputBufferNull, // is NULL
		PXActionRefuedInputBufferEmpty, // has no data, adress is not NULL but the data is
		PXActionRefuedInputBufferTooSmal, // cant 
	
		PXActionRefuedOutputBufferNull, // is NULL 
		PXActionRefuedOutputBufferTooSmal, // 


		//---<File-General>------------------
		PXActionRefusedEmptyFilePath,
		PXActionFailedFileNotFound,

		PXActionFailedFileMapping,// mmap() / CreateViewofFile() failed

		PXActionFailedFileCreate,
		PXActionFailedFileDelete,
		PXActionFailedFileOpen,
		PXActionFailedFileClose,
		PXActionFailedFileWrite,
		PXActionFailedFileRead,

		//---<Socket>---------------------
		PXActionFailedSocketRecieve,
		PXActionFailedSocketSend,
		PXActionRefusedSocketNotConnected,

		PXActionFailedSocketConnect,
		PXActionFailedSocketCreation,
		PXActionFailedSocketOption,
		PXActionFailedSocketBinding,
		PXActionFailedSocketListening,

		PXActionRefusedSocketInavlidAdressFamily,
		PXActionRefusedSocketInvalidFlags,
		PXActionRefusedNameServerIsTemporaryOffline,
		PXActionRefusedNameServerIsPermanentOffline,
		PXActionRefusedSocketTypeNotSupported,
		PXActionRefusedRequestedAddressFamilyNotSupported,
		PXActionRefusedHostExistsButHasNoData,
		PXActionRefusedHostHasNoNetworkAddresses,
		PXActionRefusedIPOrPortNotKnown,
		//-----------------------------------

		//---<File-Parsing>-------------------
		PXActionFailedFormatNotDetected,
		PXActionRefusedFormatNotSupported,
		PXActionFailedFormatInvalid,
		PXActionFailedFormatNotAsExpected,
		PXActionRefusedInvalidHeaderSignature,
		PXActionRefusedInvalidVersion,
		//-----------------------------------

		//---<File-Writing>------------------
		PXActionRefusedFormatSettingNotAllowed,
		//-----------------------------------


		//---<Graphics>-----------------------
		PXActionFailedResourceRegister,
		PXActionRefusedResourceRegister,
		PXActionRefusedResourceDelete,
		//------------------------------------



		RequestedServiceNotAvailableForSocket,


		//---<Server>------------------------
		NoPXClientWithThisID,
		//-----------------------------------

		//---<Compiler>----------------------
		PXActionCompilingError,
		//-----------------------------------

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
	PXActionResult;

#define PXActionExitOnSuccess(actionResult) if (PXActionSuccessful == actionResult) return PXActionSuccessful;
#define PXActionExitOnError(actionResult) if (PXActionSuccessful != actionResult) return actionResult;
#define PXActionOnErrorFetchAndExit(b) if(b) { return GetCurrentError(); }

	PXPublic PXActionResult ConvertErrorCode(const int errorCode);
	PXPublic PXActionResult GetCurrentError();

#ifdef __cplusplus
}
#endif

#endif