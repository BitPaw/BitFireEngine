#include "FileTemporary.h"

#include "../OSDefine.h"
#include <string>
#include <cassert>

BF::FileActionResult BF::FileTemporary::Open(const char* filePath, FileOpenMode fileOpenMode)
{
    const char* readMode = nullptr;

    switch (fileOpenMode)
    {
        case BF::FileOpenMode::Read:
            readMode = FileReadMode;
            break;

        case BF::FileOpenMode::Write:
            readMode = FileWriteMode;
            break;
    }

    assert(readMode != nullptr);

#if defined(OSUnix)
    FileMarker = popen(filePath, readMode);
#elif defined(OSWindows)
    FileMarker = _popen(filePath, readMode);
#endif 

    return FileMarker ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
}

BF::FileActionResult BF::FileTemporary::Open(const wchar_t* filePath, FileOpenMode fileOpenMode)
{
    const wchar_t* readMode = nullptr;

    switch (fileOpenMode)
    {
        case BF::FileOpenMode::Read:
            readMode = FileReadModeW;
            break;

        case BF::FileOpenMode::Write:
            readMode = FileWriteModeW;
            break;
    }

    assert(readMode != nullptr);

#if defined(OSUnix)
    FileMarker = wpopen(filePath, readMode);
#elif defined(OSWindows)
    FileMarker = _wpopen(filePath, readMode);
#endif 

    return FileMarker ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
}

BF::FileActionResult BF::FileTemporary::Close()
{
    int closeResult = -1;

#if defined(OSUnix)
    closeResult =  pclose(FileMarker);
#elif defined(OSWindows)
    closeResult = _pclose(FileMarker);
#endif   

    FileMarker = nullptr;

    switch (closeResult)
    {
        case 0:
            return FileActionResult::Successful;

        default:
            return FileActionResult::FileCloseFailure;
    }
}