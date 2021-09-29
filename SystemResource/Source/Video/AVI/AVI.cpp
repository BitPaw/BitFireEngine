#include "AVI.h"
#include "../../File/File.h"

BF::ResourceLoadingResult BF::AVI::Load(const char* filePath)
{
    File file(filePath);
    ResourceLoadingResult loadingResult = file.ReadFromDisk();

    if (loadingResult != ResourceLoadingResult::Successful)
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

    return ResourceLoadingResult::Successful;
}

BF::ResourceLoadingResult BF::AVI::Save(const char* filePath)
{
    return ResourceLoadingResult();
}
