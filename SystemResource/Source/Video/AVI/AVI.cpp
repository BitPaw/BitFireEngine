#include "AVI.h"
#include "../../File/FileStream.h"

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
        char expectedRIFFSignature[4];

        fileStream.Read(expectedRIFFSignature, 4u);       ;

        bool validRIFF = fileStream.ReadAndCompare("RIFF", 4u);
    }

    unsigned int size = 0;
  
    fileStream.Read(size, Endian::Big);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::AVI::Save(const char* filePath)
{
    return FileActionResult();
}
