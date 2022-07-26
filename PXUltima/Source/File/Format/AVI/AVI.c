#include "AVI.h"

#include <File/Format/RIFF/RIFF.h>

ActionResult AVIParse(AVI* avi, const void* data, const size_t dataSize, size_t* dataRead)
{
    /*
    File file;

    {
        const ActionResult loadingResult = file.MapToVirtualMemory(filePath, MemoryReadOnly);

        if(loadingResult != ResultSuccessful)
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
            return ResultFormatNotAsExpected;
        }
    }

    unsigned int size = 0;

    file.Read(size, EndianBig);
    */

    return ResultInvalid;
}