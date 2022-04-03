#include "FileTemporary.h"

#include <OS/OSDefine.h>
#include <string>
#include <cassert>

#if defined(OSUnix)
#define PipeOpen popen
#define PipeOpenW(wchar, mode) popen((char*)wchar, (const char*) mode) // TODO: instable
#define PipeClose pclose
#elif defined(OSWindows)
#define PipeOpen _popen
#define PipeOpenW _wpopen
#define PipeClose _pclose
#endif  

BF::FileActionResult BF::FileTemporary::Open(const char* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
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

    FileMarker = PipeOpen(filePath, readMode);

    if (!FileMarker)
    {
        return FileActionResult::FileNotFound;
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::FileTemporary::Open(const wchar_t* filePath, FileOpenMode fileOpenMode, FileCachingMode fileCachingMode)
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

    FileMarker = PipeOpenW(filePath, readMode);

    return FileMarker ? FileActionResult::Successful : FileActionResult::FileOpenFailure;
}

BF::FileActionResult BF::FileTemporary::Close()
{
    int closeResult = PipeClose(FileMarker);

    FileMarker = nullptr;

    switch (closeResult)
    {
        case 0:
            return FileActionResult::Successful;

        default:
            return FileActionResult::FileCloseFailure;
    }
}