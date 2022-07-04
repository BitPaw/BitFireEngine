#include "AVI.h"

#include <File/File.h>
#include <Media/RIFF/RIFF.h>

BF::FileActionResult BF::AVI::Load(const char* filePath)
{
    File file;
    
    {
        const FileActionResult loadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);

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
  
    file.Read(size, Endian::Big);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::AVI::Save(const char* filePath)
{
    return FileActionResult();
}