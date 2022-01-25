#include "FileCachingMode.h"
#include "../OSDefine.h"

#define FileCachingModeDefault 0 //POSIX_FADV_NORMAL

#if defined(OSUnix)
// from <fcntl.h>
#define FileCachingModeSequentialScan 2 // POSIX_FADV_SEQUENTIAL
#define FileCachingModeRandomAccess  1 // POSIX_FADV_RANDOM
#define FileCachingModeWillNeed 3 // POSIX_FADV_WILLNEED
#define FileCachingModeDontNeed 4 // POSIX_FADV_DONTNEED
#define FileCachingModeNoReuse 5 // POSIX_FADV_NOREUSE
#elif defined(OSWindows)
// From WinBase.h   
#define FileCachingModeWriteThrough      0x80000000 // FILE_FLAG_WRITE_THROUGH
#define FileCachingModeOverLapped        0x40000000
#define FileCachingModeNoBuffering       0x20000000 // FILE_FLAG_NO_BUFFERING
#define FileCachingModeRandomAccess      0x10000000 // FILE_FLAG_RANDOM_ACCESS
#define FileCachingModeSequentialScan    0x08000000 // FILE_FLAG_SEQUENTIAL_SCAN
#define FileCachingModeDeleteOnClose     0x04000000
#define FileCachingModeBackUpSemantics   0x02000000
#define FileCachingModePOSIXSemantics    0x01000000
#define FileCachingModeSessionAware      0x00800000
#define FileCachingModeOpenReparsePoint  0x00200000
#define FileCachingModeOpenNoRecall      0x00100000
#define FileCachingModeFirstPipeInstance 0x00080000

// WinNT.h
// FILE_ATTRIBUTE_TEMPORARY
#endif

BF::FileCachingMode BF::ConvertFileCachingMode(unsigned int value)
{
	return FileCachingMode::Default;
}

unsigned int BF::ConvertFileCachingMode(FileCachingMode fileCachingMode)
{
    switch (fileCachingMode)
    {
        default:
        case BF::FileCachingMode::Default:
            return FileCachingModeDefault;

        case BF::FileCachingMode::Random:
            return FileCachingModeRandomAccess;

        case BF::FileCachingMode::Sequential:
            return FileCachingModeSequentialScan;

       // case BF::FileCachingMode::Temporary:
       //     break;

       // case BF::FileCachingMode::UseOnce:
       //     break;

       // case BF::FileCachingMode::NoBuffering:
       //     return FileCachingModeNoBuffering;

       // case BF::FileCachingMode::NeedLater:
       //     return FileCachingModeDontNeed;

       // case BF::FileCachingMode::DontNeedNow:
       //     return FileCachingModeNoReuse;
    }
}