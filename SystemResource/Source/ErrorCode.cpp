#include "ErrorCode.h"

#include "OSDefine.h"

#if defined(OSUnix)
	#include <errno.h>
	#define EOTHER -1
#elif defined(OSWindows)
	#include <windows.h>
#endif

int BF::ConvertErrorCode(ErrorCode errorCode)
{
	switch (errorCode)
	{
		default:
		case BF::ErrorCode::UnkownError:
			return EOTHER;

		case BF::ErrorCode::PermissionDenied:
			return EPERM;

		case BF::ErrorCode::AddressInUse:
			return 0000;

		case BF::ErrorCode::AddressNotAvailable:
			return 0000;

		case BF::ErrorCode::AddressFamilyNotSupported:
			return 0000;

		case BF::ErrorCode::ResourceUnavailableTryAgain:
			return 0000;

		case BF::ErrorCode::ConnectionAlreadyInProgress:
			return 0000;

		case BF::ErrorCode::ArgumentListTooLong:
			return 0000;

		case BF::ErrorCode::BadFileDescriptor:
			return 0000;

		case BF::ErrorCode::BadMessage:
			return 0000;

		case BF::ErrorCode::DeviceOrResourceBusy:
			return 0000;

		case BF::ErrorCode::OperationCanceled:
			return 0000;

		case BF::ErrorCode::NoChildProcesses:
			return 0000;

		case BF::ErrorCode::ConnectionAborted:
			return 0000;

		case BF::ErrorCode::ConnectionRefused:
			return 0000;

		case BF::ErrorCode::ConnectionReset:
			return 0000;

		case BF::ErrorCode::ResourceDeadlockWouldOccur:
			return 0000;

		case BF::ErrorCode::DestinationAddressRequired:
			return 0000;

		case BF::ErrorCode::MathematicsArgumentOutOfDomainOfFunction:
			return 0000;

		case BF::ErrorCode::FileExists:
			return 0000;

		case BF::ErrorCode::BadAddress:
			return 0000;

		case BF::ErrorCode::FileTooLarge:
			return 0000;

		case BF::ErrorCode::HostIsUnreachable:
			return 0000;

		case BF::ErrorCode::IdentifierRemoved:
			return 0000;

		case BF::ErrorCode::IllegalByteSequence:
			return 0000;

		case BF::ErrorCode::OperationInProgress:
			return 0000;

		case BF::ErrorCode::InterruptedFunction:
			return 0000;

		case BF::ErrorCode::InvalidArgument:
			return 0000;

		case BF::ErrorCode::IOFailure:
			return 0000;

		case BF::ErrorCode::SocketIsConnected:
			return 0000;

		case BF::ErrorCode::IsADirectory:
			return 0000;

		case BF::ErrorCode::TooManyLevelsOfSymbolicLinks:
			return 0000;

		case BF::ErrorCode::FileDescriptorValueTooLarge:
			return 0000;

		case BF::ErrorCode::TooManyLinks:
			return 0000;

		case BF::ErrorCode::MessageTooLarge:
			return 0000;

		case BF::ErrorCode::FilenameTooLong:
			return 0000;

		case BF::ErrorCode::NetworkIsDown:
			return 0000;

		case BF::ErrorCode::ConnectionAbortedByNetwork:
			return 0000;

		case BF::ErrorCode::NetworkUnreachable:
			return 0000;

		case BF::ErrorCode::TooManyFilesOpenInSystem:
			return 0000;

		case BF::ErrorCode::NoBufferSpaceAvailable:
			return 0000;

		case BF::ErrorCode::NoMessageIsAvailableOnTheStreamHeadReadQueue:
			return 0000;

		case BF::ErrorCode::NoSuchDevice:
			return 0000;

		case BF::ErrorCode::NoSuchFileOrDirectory:
			return 0000;

		case BF::ErrorCode::ExecutableFileFormatError:
			return 0000;

		case BF::ErrorCode::NoLocksAvailable:
			return 0000;

		case BF::ErrorCode::LinkHasBeenSevered:
			return 0000;

		case BF::ErrorCode::OutOfMemory:
			return 0000;

		case BF::ErrorCode::NoMessageOfTheDesiredType:
			return 0000;

		case BF::ErrorCode::ProtocolNotAvailable:
			return 0000;

		case BF::ErrorCode::NoSpaceLeftOnDevice:
			return 0000;

		case BF::ErrorCode::NoStreamResources:
			return 0000;

		case BF::ErrorCode::NotAStream:
			return 0000;

		case BF::ErrorCode::FunctionNotSupported:
			return 0000;

		case BF::ErrorCode::TheSocketIsNotConnected:
			return 0000;

		case BF::ErrorCode::NotADirectory:
			return 0000;

		case BF::ErrorCode::DirectoryNotEmpty:
			return 0000;

		case BF::ErrorCode::StateNotRecoverable:
			return 0000;

		case BF::ErrorCode::NotASocket:
			return 0000;

		case BF::ErrorCode::NotSupported:
			return 0000;

		case BF::ErrorCode::InappropriateIOControlOperation:
			return 0000;

		case BF::ErrorCode::NoSuchDeviceOrAddress:
			return 0000;

		case BF::ErrorCode::OperationNotSupportedOnSocket:
			return 0000;

		case BF::ErrorCode::ValueTooLargeToBeStoredInDataType:
			return 0000;

		case BF::ErrorCode::PreviousOwnerDied:
			return 0000;

		case BF::ErrorCode::OperationNotPermitted:
			return 0000;

		case BF::ErrorCode::BrokenPipe:
			return 0000;

		case BF::ErrorCode::ProtocolError:
			return 0000;

		case BF::ErrorCode::ProtocolNotSupported:
			return 0000;

		case BF::ErrorCode::ProtocolWrongTypeForSocket:
			return 0000;

		case BF::ErrorCode::ResultTooLarge:
			return 0000;

		case BF::ErrorCode::ReadOnlyFileSystem:
			return 0000;

		case BF::ErrorCode::InvalidSeek:
			return 0000;

		case BF::ErrorCode::NoSuchProcess:
			return 0000;

		case BF::ErrorCode::StreamTimeout:
			return 0000;

		case BF::ErrorCode::ConnectionTimedOut:
			return 0000;

		case BF::ErrorCode::TextFileBusy:
			return 0000;

		case BF::ErrorCode::OperationWouldBlock:
			return 0000;

		case BF::ErrorCode::CrossDeviceLink:
			return 0000;
	}
}

BF::ErrorCode BF::ConvertErrorCode(int errorCode)
{
	switch (errorCode)
	{
		default:
		case EOTHER:
			return  BF::ErrorCode::UnkownError;

		case EACCES:
			return  BF::ErrorCode::PermissionDenied;

		case EADDRINUSE:
			return  BF::ErrorCode::AddressInUse;

		case EADDRNOTAVAIL:
			return  BF::ErrorCode::AddressNotAvailable;

		case EAFNOSUPPORT:
			return  BF::ErrorCode::AddressFamilyNotSupported;		

		case EALREADY:
			return  BF::ErrorCode::ConnectionAlreadyInProgress;

		case E2BIG:
			return  BF::ErrorCode::ArgumentListTooLong;

		case EBADF:
			return  BF::ErrorCode::BadFileDescriptor;

		case EBADMSG:
			return  BF::ErrorCode::BadMessage;

		case EBUSY:
			return  BF::ErrorCode::DeviceOrResourceBusy;

		case ECANCELED:
			return  BF::ErrorCode::OperationCanceled;

		case ECHILD:
			return  BF::ErrorCode::NoChildProcesses;

		case ECONNABORTED:
			return  BF::ErrorCode::ConnectionAborted;

		case ECONNREFUSED:
			return  BF::ErrorCode::ConnectionRefused;

		case ECONNRESET:
			return  BF::ErrorCode::ConnectionReset;

		case EDEADLK:
			return  BF::ErrorCode::ResourceDeadlockWouldOccur;

		case EDESTADDRREQ:
			return  BF::ErrorCode::DestinationAddressRequired;

		case EDOM:
			return  BF::ErrorCode::MathematicsArgumentOutOfDomainOfFunction;

		case EEXIST:
			return  BF::ErrorCode::FileExists;

		case EFAULT:
			return  BF::ErrorCode::BadAddress;

		case EFBIG:
			return  BF::ErrorCode::FileTooLarge;

		case EHOSTUNREACH:
			return  BF::ErrorCode::HostIsUnreachable;

		case EIDRM:
			return  BF::ErrorCode::IdentifierRemoved;

		case EILSEQ:
			return  BF::ErrorCode::IllegalByteSequence;

		case EINPROGRESS:
			return  BF::ErrorCode::OperationInProgress;

		case EINTR:
			return  BF::ErrorCode::InterruptedFunction;

		case EINVAL:
			return  BF::ErrorCode::InvalidArgument;

		case EIO:
			return  BF::ErrorCode::IOFailure;

		case EISCONN:
			return  BF::ErrorCode::SocketIsConnected;

		case EISDIR:
			return  BF::ErrorCode::IsADirectory;

		case ELOOP:
			return  BF::ErrorCode::TooManyLevelsOfSymbolicLinks;

		case EMFILE:
			return  BF::ErrorCode::FileDescriptorValueTooLarge;

		case EMLINK:
			return  BF::ErrorCode::TooManyLinks;

		case EMSGSIZE:
			return  BF::ErrorCode::MessageTooLarge;

		case ENAMETOOLONG:
			return  BF::ErrorCode::FilenameTooLong;

		case ENETDOWN:
			return  BF::ErrorCode::NetworkIsDown;

		case ENETRESET:
			return  BF::ErrorCode::ConnectionAbortedByNetwork;

		case ENETUNREACH:
			return  BF::ErrorCode::NetworkUnreachable;

		case ENFILE:
			return  BF::ErrorCode::TooManyFilesOpenInSystem;

		case ENOBUFS:
			return  BF::ErrorCode::NoBufferSpaceAvailable;

		case ENODATA:
			return  BF::ErrorCode::NoMessageIsAvailableOnTheStreamHeadReadQueue;

		case ENODEV:
			return  BF::ErrorCode::NoSuchDevice;

		case ENOENT:
			return  BF::ErrorCode::NoSuchFileOrDirectory;

		case ENOEXEC:
			return  BF::ErrorCode::ExecutableFileFormatError;

		case ENOLCK:
			return  BF::ErrorCode::NoLocksAvailable;

		case ENOLINK:
			return  BF::ErrorCode::LinkHasBeenSevered;

		case ENOMEM:
			return  BF::ErrorCode::OutOfMemory;

		case ENOMSG:
			return  BF::ErrorCode::NoMessageOfTheDesiredType;

		case ENOPROTOOPT:
			return  BF::ErrorCode::ProtocolNotAvailable;

		case ENOSPC:
			return  BF::ErrorCode::NoSpaceLeftOnDevice;

		case ENOSR:
			return  BF::ErrorCode::NoStreamResources;

		case ENOSTR:
			return  BF::ErrorCode::NotAStream;

		case ENOSYS:
			return  BF::ErrorCode::FunctionNotSupported;

		case ENOTCONN:
			return  BF::ErrorCode::TheSocketIsNotConnected;

		case ENOTDIR:
			return  BF::ErrorCode::NotADirectory;

		case ENOTEMPTY:
			return  BF::ErrorCode::DirectoryNotEmpty;

		case ENOTRECOVERABLE:
			return  BF::ErrorCode::StateNotRecoverable;

		case ENOTSOCK:
			return  BF::ErrorCode::NotASocket;

		case ENOTTY:
			return  BF::ErrorCode::InappropriateIOControlOperation;

		case ENXIO:
			return  BF::ErrorCode::NoSuchDeviceOrAddress;

#if defined(OSUnix)
		//case EAGAIN:
		case EWOULDBLOCK:
			return  BF::ErrorCode::OperationWouldBlock;

		//case ENOTSUP: // fall throu, same ID unser unix.
		case ENOTSUP:
			return  BF::ErrorCode::NotSupported;

#elif defined(OSWindows)
		case EAGAIN:
			return  BF::ErrorCode::ResourceUnavailableTryAgain;

		case EWOULDBLOCK:
			return  BF::ErrorCode::OperationWouldBlock;

		case ENOTSUP:
			return  BF::ErrorCode::NotSupported;

		case EOPNOTSUPP:
			return  BF::ErrorCode::OperationNotSupportedOnSocket;
#endif	

		case EOVERFLOW:
			return  BF::ErrorCode::ValueTooLargeToBeStoredInDataType;

		case EOWNERDEAD:
			return  BF::ErrorCode::PreviousOwnerDied;

		case EPERM:
			return  BF::ErrorCode::OperationNotPermitted;

		case EPIPE:
			return  BF::ErrorCode::BrokenPipe;

		case EPROTO:
			return  BF::ErrorCode::ProtocolError;

		case EPROTONOSUPPORT:
			return  BF::ErrorCode::ProtocolNotSupported;

		case EPROTOTYPE:
			return  BF::ErrorCode::ProtocolWrongTypeForSocket;

		case ERANGE:
			return  BF::ErrorCode::ResultTooLarge;

		case EROFS:
			return  BF::ErrorCode::ReadOnlyFileSystem;

		case ESPIPE:
			return  BF::ErrorCode::InvalidSeek;

		case ESRCH:
			return  BF::ErrorCode::NoSuchProcess;

		case ETIME:
			return  BF::ErrorCode::StreamTimeout;

		case ETIMEDOUT:
			return  BF::ErrorCode::ConnectionTimedOut;

		case ETXTBSY:
			return  BF::ErrorCode::TextFileBusy;

	

		case EXDEV:
			return  BF::ErrorCode::CrossDeviceLink;
	}
}

BF::ErrorCode BF::GetCurrentError()
{
	return ConvertErrorCode(errno);
}