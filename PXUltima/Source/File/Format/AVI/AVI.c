#include "AVI.h"

#include <File/Format/RIFF/RIFF.h>

ActionResult AVIParse(AVI* avi, const void* data, const size_t dataSize, size_t* dataRead)
{
    /*
    File file;

    {
        const FileActionResult loadingResult = file.MapToVirtualMemory(filePath, MemoryReadOnly);

        if(loadingResult != FileActionResult::Successful)
        {
            return loadingResult;
        }
    }

    // RIFF
    {
        RIFF riff;

        // riff.Parse(fileStream);

        if(!riff.Valid)
        {
            return FileActionResult::FormatNotAsExpected;
        }
    }

    unsigned int size = 0;

    file.Read(size, EndianBig);
    */

    return ResultInvalid;
}