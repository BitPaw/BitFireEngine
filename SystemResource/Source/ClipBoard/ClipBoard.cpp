#include "ClipBoard.h"

#include <OS/OSVersion.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <wtypes.h>
#include <WinUser.h>
#endif

ActionResult BF::ClipBoard::Open()
{
#if defined(OSUnix)
  return ResultInvalid;

#elif defined(OSWindows)
	HWND CWindowID = NULL;
	bool success = OpenClipboard(CWindowID);

	if (!success)
	{
		return GetCurrentError();
	}

	return ResultSuccessful;
#endif
}

bool BF::ClipBoard::Close()
{
#if defined(OSUnix)
#elif defined(OSWindows)
	return CloseClipboard();
#endif
}

ActionResult BF::ClipBoard::Set(const ClipBoardFormat format, const void* data)
{
#if defined(OSUnix)
    return ResultInvalid;

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

	return ResultSuccessful;
#endif
}

bool BF::ClipBoard::Clear()
{
#if defined(OSUnix)
  return ResultInvalid;

#elif defined(OSWindows)
	return EmptyClipboard();
#endif
}
