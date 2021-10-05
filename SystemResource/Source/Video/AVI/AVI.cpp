#include "AVI.h"
#include "../../File/File.h"

BF::FileActionResult BF::AVI::Load(const char* filePath)
{
    File file(filePath);
    FileActionResult loadingResult = file.ReadFromDisk();

    if (loadingResult != FileActionResult::Successful)
    {
        return loadingResult;
    }


    // RIFF
    {
        char expectedRIFFSignature[4];

        file.Read(expectedRIFFSignature, 4u);

        bool validRIFF = memcmp("RIFF", expectedRIFFSignature, 4u) == 0;
    }

    unsigned int size = 0;
  
    file.Read(size, Endian::Big);

    return FileActionResult::Successful;
}

BF::FileActionResult BF::AVI::Save(const char* filePath)
{
    return FileActionResult();
}
