#include "TIFF.h"

#include <File/FileStream.h>

#define GIFFormatA {'I','I'}
#define GIFFormatB {'M','M'}

BF::TIFF::TIFF()
{

}

BF::FileActionResult BF::TIFF::Load(const wchar_t* filePath)
{
    FileStream fileStream;
    FileActionResult loadingResult = fileStream.ReadFromDisk(filePath);

    if (loadingResult != FileActionResult::Successful)
    {
        return loadingResult;
    }

    // Check Header
    {
        const char versionA[2] = GIFFormatA;
        const char versionB[2] = GIFFormatB;
        char headerTag[2] = { '#', '#' };

       fileStream.Read(headerTag, sizeof(headerTag));

        bool useBigEndian = headerTag[0] == versionB[0] && headerTag[1] == versionB[1];
        bool useLittleEndian = headerTag[0] == versionA[0] && headerTag[1] == versionA[1];
        bool validVersion = useBigEndian != useLittleEndian;

        if (!validVersion)
        {
            return FileActionResult::InvalidVersion;
        }
    }

    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::Save(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::ConvertTo(Image& image)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TIFF::ConvertFrom(Image& image)
{
    return FileActionResult::Successful;
}