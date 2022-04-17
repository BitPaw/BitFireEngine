#include "AVI.h"
#include <File/FileStream.h>
#include <Media/RIFF/RIFF.h>

BF::FileActionResult BF::AVI::Load(const char* filePath)
{
    FileStream fileStream;
    FileActionResult loadingResult = fileStream.ReadFromDisk(filePath);

    if (loadingResult != FileActionResult::Successful)
    {
        return loadingResult;
    }


    // RIFF
    {
        RIFF riff;

        riff.Parse(fileStream);

        if(!riff.Valid)
        {
            return FileActionResult::FormatNotAsExpected;
        }
    }

    unsigned int size = 0;
  
    fileStream.Read(size, Endian::Big);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::AVI::Save(const char* filePath)
{
    return FileActionResult();
}
