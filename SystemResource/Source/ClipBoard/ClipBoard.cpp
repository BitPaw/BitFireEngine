#include "ClipBoard.h"

#include "../OSDefine.h"

#if defined(OSUnix)
#elif defined(OSWindows)
#include <wtypes.h>
#include <WinUser.h>
#endif

BF::ErrorCode BF::ClipBoard::Open()
{
#if defined(OSUnix)
#elif defined(OSWindows)
	HWND windowID = NULL;
	bool success = OpenClipboard(windowID);

	if (!success)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
#endif
}

bool BF::ClipBoard::Close()
{
#if defined(OSUnix)
#elif defined(OSWindows)
	return CloseClipboard();
#endif
}

BF::ErrorCode BF::ClipBoard::Set(const ClipBoardFormat format, const void* data)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	// Alloc something with GlobalAlloc()
	// Maybe copy data?

	const HGLOBAL memory = nullptr;
	const unsigned int formatID = ToClipBoardFormat(format);
	const HANDLE handle = SetClipboardData(formatID, memory);
	const bool successful = handle != nullptr;

	if (!successful)
	{
		return GetCurrentError();
	}

	return ErrorCode::Successful;
#endif	
}

bool BF::ClipBoard::Clear()
{
#if defined(OSUnix)
#elif defined(OSWindows)
	return EmptyClipboard();
#endif
}